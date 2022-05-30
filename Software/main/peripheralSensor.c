#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_system.h"
#include "esp_err.h"
#include "driver/i2c.h"


#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "lvgl_usbSensor_create.h"
#include "lvgl_digitclock_create.h"
#include "mqtt_client.h"
#include "mqtt_app.h"

#define TAG "periSensor"
#define INA226_I2C_ADDR 0x40
#define SHT31_I2C_ADDR 0x44


static esp_err_t i2c0_master_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = 1,
        .scl_io_num = 0,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000,
    };

    i2c_param_config(0,&conf);

    return i2c_driver_install(0, conf.mode, 0, 0, 0);
}

static esp_err_t ina226_reg_write(uint8_t addr,int16_t data)
{
    uint8_t write_buf[3] = {addr, (data>>8),data&0xff};

    return i2c_master_write_to_device(0, INA226_I2C_ADDR, write_buf, 3, 1000 / portTICK_PERIOD_MS);
}

static esp_err_t ina226_reg_read(uint8_t addr,int16_t* data)
{
    uint8_t ori_data[2];
    esp_err_t err_t;
    err_t = i2c_master_write_read_device(0, INA226_I2C_ADDR, &addr, 1, ori_data, 2, 1000 / portTICK_PERIOD_MS);
    *data  = ((int16_t)ori_data[0]<<8) + (int16_t)ori_data[1];
    return err_t;
}

static esp_err_t ina226_init(void)
{
    /*
    ESP_ERROR_CHECK(i2c0_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");
    */

    int16_t data;
    ESP_ERROR_CHECK(ina226_reg_read(0xfe,&data));
    ESP_LOGI(TAG, "INA226 0xFE: %x",data);

    if(data == 0x5449)
    {
        ESP_LOGI(TAG, "INA226 check ok");
    }
    else
    {
        ESP_LOGE(TAG, "INA226 Unknow device Info");
        return ESP_FAIL;
    }

    ESP_ERROR_CHECK(ina226_reg_write(0x00,0x8000)); //soft reset
    vTaskDelay(pdMS_TO_TICKS(100)); //等待100ms
    ESP_ERROR_CHECK(ina226_reg_write(0x00,0x4327));
    ESP_ERROR_CHECK(ina226_reg_write(0x05,341)); //电流 LSBU = 1 mA
    ESP_LOGI(TAG, "INA226 init OK");
    return ESP_OK;
}

esp_err_t ina226_voltage_read(int32_t* volt)
{
    int16_t volt_ori;
    esp_err_t err_t;
    err_t = ina226_reg_read(0x02,&volt_ori);

    *volt = (int32_t)volt_ori*125/100; //单位毫伏
    return err_t;
}

esp_err_t ina226_shutvolt_read(int32_t* volt)
{
    int16_t shutvolt_ori;
    esp_err_t err_t;
    err_t = ina226_reg_read(0x01,&shutvolt_ori);

    *volt = (int32_t)shutvolt_ori;
    return err_t;
}

esp_err_t ina226_current_read(int32_t* curr)
{
    int16_t curr_ori;
    esp_err_t err_t;
    err_t = ina226_reg_read(0x04,&curr_ori);

    *curr = (int32_t)curr_ori; //单位毫伏
    return err_t;
}

static esp_err_t sht31_init(void)
{
    esp_err_t err_t;
    uint8_t send_buf[2];
    uint8_t recv_buf[6];

    // IO 3 是sht31dis的复位引脚
    gpio_reset_pin(3);
    gpio_set_direction(3,GPIO_MODE_OUTPUT);
    gpio_set_level(3,0); //下拉
    vTaskDelay( pdMS_TO_TICKS(1) ); //1ms的下拉脉冲
    gpio_set_level(3,1);
    vTaskDelay( pdMS_TO_TICKS(10) ); //等待启动

    //CMD_READ_SERIALNBR = 0xF32D <- 读status
    send_buf[0] = 0xF3;
    send_buf[1] = 0x2D;
    err_t = i2c_master_write_read_device(0, SHT31_I2C_ADDR, send_buf, 2, recv_buf, 3, 1000 / portTICK_PERIOD_MS);
    if( err_t == ESP_OK)
    {
        ESP_LOGI(TAG, "SHT31 status Register: %x %x CRC: %x",recv_buf[0],recv_buf[1],recv_buf[2]);
    }
    else
    {
        ESP_LOGE(TAG,"SHT31 not Found...Err:0x%x",err_t);
        return ESP_FAIL;
    }

    //设置为循环工作状态 0x2236 2Hz High Repeatability
    send_buf[0] = 0x22;
    send_buf[1] = 0x36;
    err_t = i2c_master_write_to_device(0, SHT31_I2C_ADDR, send_buf, 2, 1000 / portTICK_PERIOD_MS);
    if( err_t==ESP_ERR_TIMEOUT )
    {
        ESP_LOGW(TAG, "SHT31 Write, But i2c bus busy...");
        return ESP_ERR_TIMEOUT;
    }
    else if( err_t == ESP_OK)
    {
        ESP_LOGI(TAG, "SHT31 Set Success...");
        return ESP_OK;
    }
    else
    {
        return ESP_FAIL;
    }
}

static esp_err_t sht31_read(uint16_t* temp,uint16_t* rh)
{
    esp_err_t err_t;
    uint8_t send_buf[2] = {0xe0,0x00};
    uint8_t recv_buf[6] = {0};

    err_t = i2c_master_write_read_device(0,SHT31_I2C_ADDR,send_buf,2,recv_buf,6,1000 / portTICK_PERIOD_MS);
    if(err_t==ESP_OK)
    {
        *temp = ((uint16_t)recv_buf[0]<<8)+recv_buf[1];
        *rh = ((uint16_t)recv_buf[3]<<8)+recv_buf[4];
    }
    return err_t;
}

void peripheralsensorTask(void *pvParameter)
{
    esp_err_t err_ina226,err_sht31;
    int32_t vlot_data;
    int32_t curr_data;
    int32_t numberlen;
    uint16_t statetick=0;
    uint16_t temperature_data;
    uint16_t rhumidity_data;
    char numberstring[10] = {};

    ESP_ERROR_CHECK(i2c0_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    err_ina226 = ina226_init();
    err_sht31 = sht31_init();

    while(1)
    {
        statetick++;
        //循环 采集和发送usb 和 温湿度
        if( err_ina226 == ESP_OK )
        {
            ina226_voltage_read(&vlot_data);
            usbSensor_voltageNumber_set(vlot_data);
            ESP_LOGI(TAG, "INA226 voltage = %d",vlot_data);

            ina226_shutvolt_read(&curr_data);
            curr_data = (~curr_data)+1; //硬件中已经反接了V+和V-
            curr_data = curr_data*8192/0x7fff; //得到采样电阻上的电压
            curr_data = curr_data*100/15; //得到电流 采样电阻15m Ohm 
            //电流的计算 I*10000 (A) 即 12554等于1.2554A 
            usbSensor_currentNumber_set(curr_data);
            ESP_LOGI(TAG, "INA226 current = %d",curr_data);
            
            usbSensor_wattNumb_set(vlot_data*curr_data/1000);

            if(curr_data!=0)
            {
                usbSensor_ohmNumb_set(vlot_data*1000/curr_data);
            }
            else
            {
                usbSensor_ohmNumb_set(0);
            }

            if(xEventGroupWaitBits(g_wifi_event_group, MQTTC_CONNECTED_OK,false,false, 0))
            {
                //已经连接上MQTT服务器
                numberlen = sprintf(numberstring,"%d.%03d",vlot_data/1000,vlot_data%1000);
                esp_mqtt_client_publish(mqtt_appclient,MQTT_UNIQUE_ID"/usb/voltage",numberstring,numberlen,0,0);

                numberlen = sprintf(numberstring,"%d.%04d",curr_data/10000,curr_data%10000);
                esp_mqtt_client_publish(mqtt_appclient,MQTT_UNIQUE_ID"/usb/current",numberstring,numberlen,0,0);
            }
        }
        else
        {
            ESP_LOGW(TAG,"reinitial ina226...");
            err_ina226 = ina226_init();
        }

        if( (err_sht31 == ESP_OK)&&((statetick%3)==0))
        {
            sht31_read(&temperature_data,&rhumidity_data);
            ESP_LOGI(TAG,"sht31 [orig] temperature = %d , humidity = %d",temperature_data,rhumidity_data);
            temperature_data = -4500+(uint32_t)17500*temperature_data/0xffff; //小数点后两位
            rhumidity_data = 10000*(uint32_t)rhumidity_data/0xffff; //小数点后两位

            digitclock_setTempHumi((int16_t)temperature_data,rhumidity_data);

            if(xEventGroupWaitBits(g_wifi_event_group, MQTTC_CONNECTED_OK,false,false, 0))
            {
                //已经连接上MQTT服务器
                numberlen = sprintf(numberstring,"%d.%02d",temperature_data/100,vlot_data%100);
                esp_mqtt_client_publish(mqtt_appclient,MQTT_UNIQUE_ID"/clk/temperature",numberstring,numberlen,0,0);

                numberlen = sprintf(numberstring,"%d.%02d",rhumidity_data/100,rhumidity_data%100);
                esp_mqtt_client_publish(mqtt_appclient,MQTT_UNIQUE_ID"/clk/humidity",numberstring,numberlen,0,0);
            }
        }


        vTaskDelay(pdMS_TO_TICKS(250)); //分频大概到250ms
    }
}