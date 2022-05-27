#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"


#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LVGL_MAINTHREAD_CREATE_
#define LVGL_MAINTHREAD_CREATE_

extern EventGroupHandle_t g_lvgl_event_group;
extern SemaphoreHandle_t xGuiSemaphore;
extern void guiTask(void *pvParameter);

#endif

/*
if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        // FUNCTION
        
        xSemaphoreGive(xGuiSemaphore);
    }
*/