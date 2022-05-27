#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LVGL_NETINFO_CREATE_H_
#define LVGL_NETINFO_CREATE_H_

extern void networkInfo_wifiInfoStatus_set(char* str_WIFIstatus);
extern void networkInfo_wifiInfoSSID_set(char* str_WIFIname);

extern void networkInfo_ipAdmInfo_set(char* ipaddress,char* ipmask,char* gateway);
extern void networkInfo_mqttClientInfo_set(char* str_MQTTstatus);
extern void screen_networkInfo_create(lv_obj_t* parent);

#endif