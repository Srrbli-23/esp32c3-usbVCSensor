#ifndef MQTT_APP_H_
#define MQTT_APP_H_

#if CONFIG_MQTT_USERGEN_UNIQUE_ID
#define MQTT_UNIQUE_ID CONFIG_MQTT_USERGEN_ID_STRING
// #else
// char mqtt_unique_id[20] = {0};
// ID自动生成这块还有点问题，找不到优雅的替代字符串的方式....
#endif

#define MQTTC_CONNECTED_OK BIT3

extern EventGroupHandle_t g_wifi_event_group;

extern void mqtt_app_start(void);
extern esp_mqtt_client_handle_t mqtt_appclient;

#endif