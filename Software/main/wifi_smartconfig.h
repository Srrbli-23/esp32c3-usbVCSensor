
#ifndef WIFI_SMARTCONFIG_H_
#define WIFI_SMARTCONFIG_H_

#define CONNECTED_BIT       BIT0
#define ESPTOUCH_DONE_BIT   BIT1
#define WIFI_FAIL_BIT       BIT2

extern EventGroupHandle_t g_wifi_event_group;
extern void initialise_wifi(void);

#endif