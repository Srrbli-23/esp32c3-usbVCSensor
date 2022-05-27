/*
 * PROJECT:   LVGL PC Simulator using Visual Studio
 * FILE:      LVGL.Simulator.cpp
 * PURPOSE:   Implementation for LVGL ported to Windows Desktop
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>

#include "resource.h"

#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#include "lvgl/lvgl.h"
//#include "lvgl/examples/lv_examples.h"
//#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/win32drv/win32drv.h"

#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

#include <stdio.h>
#include <stdlib.h>
#include "lvgl_application_create.h"
#include "lvgl_usbSensor_create.h"
#include "lvgl_digitclock_create.h"

int main()
{
    lv_init();

    /*if (!lv_win32_init(
        GetModuleHandleW(NULL),
        SW_SHOW,
        240,
        280,
        LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_LVGL))))
    {
        return -1;
    }*/

    if (!lv_win32_init(
        GetModuleHandleW(NULL),
        SW_SHOWDEFAULT,
        280,
        240,
        LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_LVGL))))
    {
        return -1;
    }

    lv_win32_add_all_input_devices_to_group(NULL);

    lvgl_application_main_create();


    // ----------------------------------
    // Task handler loop
    // ----------------------------------

    int32_t internal_number = 0;
    int32_t voltage_test;
    int32_t current_test;
    int32_t temp_test;
    uint32_t hump_test;
    uint32_t sec = 52;

    digitclock_sntpState(0);

    digitclock_setHour(12);
    digitclock_setMinute(38);
    digitclock_setSecond(sec);

    while (!lv_win32_quit_signal)
    {
        lv_task_handler();
        Sleep(1);
        internal_number++;
        if (30==(internal_number % 100))
        {
            voltage_test = rand() % 3000 + 12000;
            current_test = rand() & 1000 + 2000;
            temp_test = rand() % 2000 + 1000;
            //temp_test = -520;
            hump_test = rand() % 7000 + 3000;
            usbSensor_voltageNumber_set(voltage_test);
            usbSensor_currentNumber_set(current_test);
            usbSensor_wattNumb_set(voltage_test*current_test/100);
            if (current_test != 0)
            {
                usbSensor_ohmNumb_set(voltage_test * 100 / current_test);
            }
            else
            {
                usbSensor_ohmNumb_set(0);
            }
            digitclock_setTempHumi(temp_test, hump_test);
            digitclock_sntpState(2);
            digitclock_setDateStr("2022/05/23");
            digitclock_setWeek(6);
            digitclock_setSecond(++sec);
        }
    }

    return 0;
}
