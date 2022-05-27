
#ifndef LVGL_USBSENSOR_CREATE_H_
#define LVGL_USBSENSOR_CREATE_H_


extern void usbSensor_voltageNumber_set(int32_t voltage);
extern void usbSensor_currentNumber_set(int32_t ampele);
extern void usbSensor_wattNumb_set(int32_t watt);
extern void usbSensor_ohmNumb_set(int32_t ohm);

extern void screen_usbSensor_create(lv_obj_t* parent);

#endif