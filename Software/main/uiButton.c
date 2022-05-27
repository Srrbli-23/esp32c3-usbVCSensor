#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "lvgl_helpers.h"
#include "lvgl_application_create.h"

#define TAG "uiIO"

#define GPIO_BUTTON_NUM 9

static void buttonTask(void *pvParameter)
{
    static uint8_t lastState=0;
    static uint8_t tabview_nextID;
    while(1)
    {
        switch (lastState)
        {
        case 0:
            //检测到低电平则进入下一个状态
            if(gpio_get_level(GPIO_BUTTON_NUM)==0)
            {
                lastState = 1;
            }
            break;
        
        case 1:
            if(gpio_get_level(GPIO_BUTTON_NUM)==0)
            {
                ESP_LOGI(TAG, "BUTTON PRESS...");
                lastState = 2; //切换
                tabview_nextID = lv_tabview_get_tab_act(tabview)+1;
                if(tabview_nextID>=MAX_TABVIEW_OBJ_NUMB)
                {
                    tabview_nextID = 0;
                }
                lv_tabview_set_act(tabview, tabview_nextID, LV_ANIM_ON);
            }
            else
            {
                lastState = 0;
            }
            break;
        case 2:
            //等待按键结束
            if( gpio_get_level(GPIO_BUTTON_NUM)==1 )
            {
                ESP_LOGI(TAG, "BUTTON OUT...");
                lastState = 0;
            }
            break;
        
        default:
            lastState = 0;
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(100)); //100ms 轮询一次
    }
}

void button_init(void)
{
    gpio_reset_pin(GPIO_BUTTON_NUM);
    gpio_config_t button_conf =
    {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1<<GPIO_BUTTON_NUM,
        .pull_up_en = 1,
        .pull_down_en = 0,
    };

    gpio_config(&button_conf);
    xTaskCreate(buttonTask,"button",2048,NULL,1,NULL);
}