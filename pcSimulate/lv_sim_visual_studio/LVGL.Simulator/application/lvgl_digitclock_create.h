
#ifndef LVGL_DIGITCLOCK_CREATE_H_
#define LVGL_DIGITCLOCK_CREATE_H_

#define USER_SNTP_DEFAULT 0
#define USER_SNTP_CONNECT_WAIT 1
#define USER_SNTP_CONNECT_OK 2
#define USER_SNTP_CONNECT_FALT 3
#define USER_SNTP_CONNECT_SLEEP 4

extern void digitclock_sntpState(uint8_t state);
extern void digitclock_setTempHumi(int32_t temp, uint32_t humi);
extern void digitclock_setHour(uint8_t hour);
extern void digitclock_setMinute(uint8_t minu);
extern void digitclock_setSecond(uint8_t secd);
extern void digitclock_setDateStr(char* date);
extern void digitclock_setWeek(uint8_t week);


extern void screen_digitclock_create(lv_obj_t* parent);

#endif
