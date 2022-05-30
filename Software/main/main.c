#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_wpa2.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "mqtt_client.h"

/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_helpers.h"

#include "lvgl_mainThread.h"
#include "lvgl_usbSensor_create.h"
#include "lvgl_digitclock_create.h"
#include "mqtt_app.h"
#include "wifi_smartconfig.h"
#include "peripheralSensor.h"
#include "uiButton.h"
#include "sntp_client.h"

/*********************
 *      DEFINES
 *********************/
#define TAG "main"


EventGroupHandle_t g_wifi_event_group;

/**********************
 *   APPLICATION MAIN
 **********************/
void app_main()
{
    //ESP_ERROR_CHECK( nvs_flash_init() );

    g_wifi_event_group = xEventGroupCreate();

    // ESP32C3 必须固定到core0 （单核cpu）
    xTaskCreatePinnedToCore(guiTask, "gui", 4096 * 2, NULL, 10, NULL, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
    xEventGroupWaitBits( 
        g_lvgl_event_group, 
        0x01,
        false,
        false,
        portMAX_DELAY);
    xTaskCreate(buttonTask,"uiButton",2048,NULL,1,NULL);
    xTaskCreate(timeprocTask,"sntpTime",2048,NULL,3,NULL);
    xTaskCreate(peripheralsensorTask,"periSensor",2048,NULL,2,NULL);

    initialise_wifi();
    mqtt_app_start();

    while(1)
    {
        esp_mqtt_client_publish(mqtt_appclient, MQTT_UNIQUE_ID"/status", "Online", 0, 0, 0);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
