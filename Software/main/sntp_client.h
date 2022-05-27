
#ifndef SNTP_CLIENT_H_
#define SNTP_CLIENT_H_

extern void sntpClient_config(void);
extern void sntpClient_start(void);
extern void timeprocTask(void *pvParameter);

#endif