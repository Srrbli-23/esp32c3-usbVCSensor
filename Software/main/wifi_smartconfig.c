#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_wpa2.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_smartconfig.h"
#include "nvs.h"

#include "lvgl_netInfo_create.h"
#include "wifi_smartconfig.h"

#define WIFI_MAXMUM_RETRY 5

#define ESP_LOG_PRINTF_SELECT(X,STR_FAILED,STR_OK) if(X!=ESP_OK){ ESP_LOGI(TAG,STR_FAILED); } else { ESP_LOGI(TAG,STR_OK); }

static const char *TAG = "smartconfig";

static bool useLocalConfigureData = false;

static int s_retry_num = 0;

static void smartconfig_task(void * parm);

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        if(useLocalConfigureData)
        {
            esp_wifi_connect();
        }
        else
        {
            xTaskCreate(smartconfig_task, "smartconfig_task", 4096, NULL, 3, NULL);
        }
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        //连接报错
        if(s_retry_num < WIFI_MAXMUM_RETRY )
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
            xEventGroupClearBits(g_wifi_event_group, CONNECTED_BIT);
        }
        else
        {
            ESP_LOGI(TAG, "Failed to connect AP");
            networkInfo_wifiInfoStatus_set("failed");
            xEventGroupSetBits(g_wifi_event_group, WIFI_FAIL_BIT);
            esp_wifi_stop();
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        //获取到IP地址 可以认为已经连上wifi
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "ip:" IPSTR, IP2STR(&event->ip_info.ip));
        ESP_LOGI(TAG, "mask:" IPSTR, IP2STR(&event->ip_info.netmask));
        ESP_LOGI(TAG, "gw:" IPSTR, IP2STR(&event->ip_info.gw));
        char ip_array[4] = { IP2STR(&event->ip_info.ip) };
        char mask_array[4] = { IP2STR(&event->ip_info.netmask) };
        char gw_array[4] = { IP2STR(&event->ip_info.gw) };
        networkInfo_ipAdmInfo_set( ip_array , mask_array , gw_array );

        xEventGroupClearBits(g_wifi_event_group, WIFI_FAIL_BIT);
        xEventGroupSetBits(g_wifi_event_group, CONNECTED_BIT);
    } else if (event_base == SC_EVENT && event_id == SC_EVENT_SCAN_DONE) {
        ESP_LOGI(TAG, "Scan done");
    } else if (event_base == SC_EVENT && event_id == SC_EVENT_FOUND_CHANNEL) {
        ESP_LOGI(TAG, "Found channel");
    } else if (event_base == SC_EVENT && event_id == SC_EVENT_GOT_SSID_PSWD) {
        ESP_LOGI(TAG, "Got SSID and password");

        smartconfig_event_got_ssid_pswd_t *evt = (smartconfig_event_got_ssid_pswd_t *)event_data;
        wifi_config_t wifi_config;
        uint8_t ssid[33] = { 0 };
        uint8_t password[65] = { 0 };
        uint8_t rvd_data[33] = { 0 };

        bzero(&wifi_config, sizeof(wifi_config_t));
        memcpy(wifi_config.sta.ssid, evt->ssid, sizeof(wifi_config.sta.ssid));
        memcpy(wifi_config.sta.password, evt->password, sizeof(wifi_config.sta.password));
        wifi_config.sta.bssid_set = evt->bssid_set;
        if (wifi_config.sta.bssid_set == true) {
            memcpy(wifi_config.sta.bssid, evt->bssid, sizeof(wifi_config.sta.bssid));
        }

        memcpy(ssid, evt->ssid, sizeof(evt->ssid));
        memcpy(password, evt->password, sizeof(evt->password));
        ESP_LOGI(TAG, "SSID:%s", ssid);
        ESP_LOGI(TAG, "PASSWORD:%s", password);
        if (evt->type == SC_TYPE_ESPTOUCH_V2) {
            ESP_ERROR_CHECK( esp_smartconfig_get_rvd_data(rvd_data, sizeof(rvd_data)) );
            ESP_LOGI(TAG, "RVD_DATA:");
            for (int i=0; i<33; i++) {
                printf("%02x ", rvd_data[i]);
            }
            printf("\n");
        }

        networkInfo_wifiInfoSSID_set((char *)ssid);

        // 存储从 smartconfig 获取到的wifi信息
        nvs_handle_t wifiConfig_handle;
        esp_err_t err;
        err = nvs_open("wifiConf", NVS_READWRITE, &wifiConfig_handle);
        if (err != ESP_OK) 
        {
            ESP_LOGI(TAG,"Error (%s) opening NVS handle!\n", esp_err_to_name(err));
        } 
        else 
        {
            err = nvs_set_u32(wifiConfig_handle,"wsVersion",0x0016);
            ESP_LOG_PRINTF_SELECT(err,"write wsVersion... Failed!\n","write wsVersion... Done\n");
            err = nvs_set_blob(wifiConfig_handle,"configData",&wifi_config,sizeof(wifi_config_t));
            ESP_LOG_PRINTF_SELECT(err,"write config data... Failed!\n","write config data... Done\n");
            err = nvs_commit(wifiConfig_handle);
            ESP_LOG_PRINTF_SELECT(err,"commit... Failed!\n","commit... Done\n");
            nvs_close(wifiConfig_handle);
        }

        ESP_ERROR_CHECK( esp_wifi_disconnect() );
        ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
        esp_wifi_connect();
    } else if (event_base == SC_EVENT && event_id == SC_EVENT_SEND_ACK_DONE) {
        xEventGroupSetBits(g_wifi_event_group, ESPTOUCH_DONE_BIT);
    }
}

void initialise_wifi(void)
{
    size_t wifi_config_len = sizeof(wifi_config_t);
    // wifi_config_t wifi_config = {
    //     .sta = {
    //         .ssid = "GGGM",
    //         .password = "ak47m4a1",
    //         .threshold.authmode = WIFI_AUTH_WPA2_PSK,
    //     },
    // };
    EventBits_t uxBits;

    networkInfo_wifiInfoStatus_set("init");
    networkInfo_mqttClientInfo_set("init");

    //从 NVS 中读取已经保存过的wifi信息
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );
    nvs_handle_t wifiConfig_handle;
    err = nvs_open("wifiConf", NVS_READWRITE, &wifiConfig_handle);
    if (err != ESP_OK) 
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } 
    else 
    {
        printf("Done\n");
        // Read
        printf("Reading wifi configure from NVS ... ");
        //使用U32也许会对齐？
        uint32_t wifiConfig_wsVersion; // 存储wifi configure subblock的版本，主要用于检验是否在NVS上存储了信息
        bool wifiConfig_isStoredData = false;
        err = nvs_get_u32(wifiConfig_handle, "wsVersion", &wifiConfig_wsVersion);
        switch (err) 
        {
            case ESP_OK:
                printf("Done\n");
                printf("wificonfig subblcok Version = 0x%x\n", wifiConfig_wsVersion);
                wifiConfig_isStoredData = true;
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("There are not wifi configure data been stored\n");
                wifiConfig_isStoredData = false;
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
                wifiConfig_isStoredData = false;
                break;
        }
        if(wifiConfig_isStoredData)
        {
            //如果已经存储了wifi的配置信息
            wifi_config_t wifi_config;
            bzero(&wifi_config, wifi_config_len);
            err = nvs_get_blob(wifiConfig_handle, "configData", &wifi_config,&wifi_config_len);
            switch (err)
            {
                case ESP_OK:
                    printf("Done\n");
                    printf("wifi apssid =%s\n",wifi_config.sta.ssid);
                    printf("wifi passwd =%s\n",wifi_config.sta.password);
                    printf("wifi authmd =%d\n",wifi_config.sta.threshold.authmode);

                    char ssid[33] = { 0 };
                    memcpy(ssid, wifi_config.sta.ssid, sizeof(wifi_config.sta.ssid));
                    networkInfo_wifiInfoSSID_set((char *)ssid);

                    useLocalConfigureData = true;
                    break;
                case ESP_ERR_NVS_NOT_FOUND:
                    printf("Error Store Data\n");
                    err = nvs_erase_key(wifiConfig_handle,"wsVersion");
                    printf((err != ESP_OK) ? "erase Failed!\n" : "erase wsVersion... Done\n");
                    err = nvs_commit(wifiConfig_handle);
                    printf((err != ESP_OK) ? "Failed!\n" : "commit... Done\n");
                    break;
                default:
                    break;
            }
        }
        // else
        // {
        //     // 如果还没存储过wifi的配置信息
        //     err = nvs_set_u32(wifiConfig_handle,"wsVersion",0x000a);
        //     printf((err != ESP_OK) ? "Failed!\n" : "write wsVersion... Done\n");
        //     err = nvs_set_blob(wifiConfig_handle,"configData",&wifi_config,wifi_config_len);
        //     printf((err != ESP_OK) ? "Failed!\n" : "write config data... Done\n");
        //     err = nvs_commit(wifiConfig_handle);
        //     printf((err != ESP_OK) ? "Failed!\n" : "commit... Done\n");
        // }
        nvs_close(wifiConfig_handle);
    }

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    networkInfo_wifiInfoStatus_set("ready");

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );

    ESP_ERROR_CHECK( esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL) );
    ESP_ERROR_CHECK( esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL) );
    ESP_ERROR_CHECK( esp_event_handler_register(SC_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL) );

    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_start() );

    uxBits = xEventGroupWaitBits( 
        g_wifi_event_group, 
        CONNECTED_BIT|WIFI_FAIL_BIT,
        false,   //不清除已连接的数据 方便其他task等待
        false,
        portMAX_DELAY);

    while(uxBits&WIFI_FAIL_BIT)
    {
        printf("try to connect wifi via espTouching...");
        useLocalConfigureData = false; //尝试使用 espTouch连接wifi
        //networkInfo_wifiInfoStatus_set("ET..");
        ESP_ERROR_CHECK( esp_wifi_start() );
        uxBits = xEventGroupWaitBits( 
            g_wifi_event_group, 
            CONNECTED_BIT|ESPTOUCH_DONE_BIT|WIFI_FAIL_BIT,
            false,   //不清除已连接的数据 方便其他task等待
            false,
            portMAX_DELAY);
    }

    printf("connect wifi success...");
    networkInfo_wifiInfoStatus_set("OK..");
    networkInfo_mqttClientInfo_set("wait");
}

static void smartconfig_task(void * parm)
{
    EventBits_t uxBits;
    ESP_ERROR_CHECK( esp_smartconfig_set_type(SC_TYPE_ESPTOUCH) );
    smartconfig_start_config_t cfg = SMARTCONFIG_START_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_smartconfig_start(&cfg) );
    while (1) {
        uxBits = xEventGroupWaitBits(g_wifi_event_group, CONNECTED_BIT | ESPTOUCH_DONE_BIT, true, false, portMAX_DELAY);
        if(uxBits & CONNECTED_BIT) {
            ESP_LOGI(TAG, "WiFi Connected to ap");
        }
        if(uxBits & ESPTOUCH_DONE_BIT) {
            ESP_LOGI(TAG, "smartconfig over");
            esp_smartconfig_stop();
            vTaskDelete(NULL);
        }
    }
}