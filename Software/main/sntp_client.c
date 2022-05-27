#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_sntp.h"

#include "sntp_client.h"
#include "wifi_smartconfig.h"

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "lvgl_digitclock_create.h"

#define TAG "sntpClient"

static TaskHandle_t xSNTPtoNotify = NULL;

static void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "Notification of a time synchronization event");
    //在回调处更新

    xTaskNotifyGive(xSNTPtoNotify);

}

void sntpClient_config(void)
{
    //连接wifi之前调用
    ESP_LOGI(TAG, "Pre-Init SNTP");

    //时区设置为中国
    setenv("TZ", "CST-8", 1);
    tzset();

#if CONFIG_LWIP_DHCP_GET_NTP_SRV
    sntp_servermode_dhcp(1);      // accept NTP offers from DHCP server, if any
#endif

}

void sntpClient_start(void)
{
    //连接wifi之后使用，自动开始运行sntp
    ESP_LOGI(TAG, "Configure SNTP");

    sntp_setoperatingmode(SNTP_OPMODE_POLL);

#if CONFIG_LWIP_DHCP_GET_NTP_SRV && SNTP_MAX_SERVERS > 1
    sntp_setservername(1, "cn.ntp.org.cn");
#if CONFIG_LWIP_DHCP_GET_NTP_SRV && SNTP_MAX_SERVERS > 2
    sntp_setservername(2, "ntp.tuna.tsinghua.edu.cn");
#endif

#if LWIP_IPV6 && SNTP_MAX_SERVERS > 3          // statically assigned IPv6 address is also possible
    ip_addr_t ip6;
    if (ipaddr_aton("2a01:3f7::1", &ip6))
    {    // ipv6 ntp source "ntp.netnod.se"
        sntp_setserver(3, &ip6);
    }
#endif  /* LWIP_IPV6 */

#else   /* LWIP_DHCP_GET_NTP_SRV && (SNTP_MAX_SERVERS > 1) */
    // otherwise, use DNS address from a pool
    sntp_setservername(0, "ntp.ntsc.ac.cn"); //默认使用腾讯云
#endif

    sntp_set_time_sync_notification_cb(time_sync_notification_cb); 

    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED); //使用平滑模式进行更新

    ESP_LOGI(TAG, "Initial SNTP...");
    sntp_init();

    ESP_LOGI(TAG, "List of configured NTP servers:");

    for (uint8_t i = 0; i < SNTP_MAX_SERVERS; ++i){
        if (sntp_getservername(i)){
            ESP_LOGI(TAG, "server %d: %s", i, sntp_getservername(i));
        } else {
            // we have either IPv4 or IPv6 address, let's print it
            char buff[48];
            ip_addr_t const *ip = sntp_getserver(i);
            if (ipaddr_ntoa_r(ip, buff, 48) != NULL)
                ESP_LOGI(TAG, "server %d: %s", i, buff);
        }
    }
}

void timeprocTask(void *pvParameter)
{
    //EventBits_t uxBits;
    uint32_t ulNotificationValue;
    static uint32_t timeToSleep = 0;
    static char datestring[12] = {0};

    time_t now;
    struct tm timeinfo;

    configASSERT( xSNTPtoNotify == NULL );
    xSNTPtoNotify = xTaskGetCurrentTaskHandle();

    sntpClient_config();
    digitclock_sntpState(USER_SNTP_DEFAULT);
    xEventGroupWaitBits(  //等待wifi连接上
        g_wifi_event_group, 
        CONNECTED_BIT,
        false,   
        false,
        portMAX_DELAY);
    sntpClient_start();
    digitclock_sntpState(USER_SNTP_CONNECT_FALT);
    while( sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET )
    {
        digitclock_sntpState(USER_SNTP_CONNECT_WAIT_A);
        vTaskDelay( pdMS_TO_TICKS(300) ); //等待0.3s
        digitclock_sntpState(USER_SNTP_CONNECT_WAIT_B);
        vTaskDelay( pdMS_TO_TICKS(300) ); //等待0.3s
    }
    // 此时已经同步上了 先设置当前时钟数据
    time(&now);
    localtime_r(&now, &timeinfo);
    digitclock_setHour(timeinfo.tm_hour);
    digitclock_setMinute(timeinfo.tm_min);
    digitclock_setSecond(timeinfo.tm_sec);

    strftime(datestring,12,"%Y/%m/%d",&timeinfo);
    digitclock_setDateStr(datestring);
    digitclock_setWeek(timeinfo.tm_wday);
    digitclock_sntpState(USER_SNTP_CONNECT_OK);
    while(1)
    {
        timeToSleep++;
        ulNotificationValue = ulTaskNotifyTake( pdTRUE, 0 ); //不等待
        if(ulNotificationValue)
        {
            //发生了更新事件
            timeToSleep = 0;
            digitclock_sntpState(USER_SNTP_CONNECT_OK);
        }
        time(&now);
        localtime_r(&now, &timeinfo);
        digitclock_setSecond(timeinfo.tm_sec);
        if(timeinfo.tm_sec == 0)
        {
            //需要更新分钟
            digitclock_setMinute(timeinfo.tm_min);
            if(timeinfo.tm_min == 0)
            {
                //需要更新小时
                digitclock_setHour(timeinfo.tm_hour);
                if((timeinfo.tm_hour==0)||(timeinfo.tm_hour==24))
                {
                    //需要更新日期
                    strftime(datestring,12,"%Y/%m/%d",&timeinfo);
                    digitclock_setDateStr(datestring);
                    digitclock_setWeek(timeinfo.tm_wday);
                }
            }
        }
        if((timeToSleep==2400)||(timeToSleep==2500))
        {
            //至少过去10分钟了
            digitclock_sntpState(USER_SNTP_CONNECT_SLEEP);
        }
        vTaskDelay( pdMS_TO_TICKS(250) ); //等待250ms
    }
}