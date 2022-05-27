#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#include "lvgl_application_create.h"
#include "lvgl_digitclock_create.h"

lv_obj_t* label_QnQ;
lv_obj_t* label_temperature;
lv_obj_t* label_humidity;

lv_obj_t* label_clkhour,*label_clkminute,*label_clksecond;

lv_obj_t* label_dateStr;
lv_obj_t* label_weekCNStr;

//const uint16_t weekCNarray[] = { 0x65e5, 0x4e00, 0x4e8c, 0x4e09, 0x56db, 0x4e94, 0x516d};
const char weekCNarray[7][4] = { "日", "一", "二", "三", "四", "五", "六" };

void digitclock_sntpState(uint8_t state)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        switch (state)
        {
        case USER_SNTP_DEFAULT:
            lv_label_set_text(label_QnQ, "QnQ");
            break;

        case USER_SNTP_CONNECT_WAIT_A:
            lv_label_set_text(label_QnQ, "0.o");
            break;
        
        case USER_SNTP_CONNECT_WAIT_B:
            lv_label_set_text(label_QnQ, "o.0");
            break;

        case USER_SNTP_CONNECT_OK:
            lv_label_set_text(label_QnQ, "^_^");
            break;

        case USER_SNTP_CONNECT_FALT:
            lv_label_set_text(label_QnQ, "#_#");
            break;

        case USER_SNTP_CONNECT_SLEEP:
            lv_label_set_text(label_QnQ, ".zZ<");
            break;

        default:
            break;
        }
        xSemaphoreGive(xGuiSemaphore);
    }
}

void digitclock_setTempHumi(int16_t temp, uint16_t humi)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        // FUNCTION
        if (temp < 0)
        {
            lv_label_set_text_fmt(label_temperature, "%02d.%02d", temp / 100, ~(temp-1) % 100);
        }
        else
        {
            lv_label_set_text_fmt(label_temperature, "%02d.%02d", temp / 100, temp % 100);
        }
        lv_label_set_text_fmt(label_humidity, "%02d.%02d", humi / 100, humi % 100);
        xSemaphoreGive(xGuiSemaphore);
    }
    
}

void digitclock_setHour(uint8_t hour)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        // FUNCTION
        lv_label_set_text_fmt(label_clkhour, "%02d", hour);
        xSemaphoreGive(xGuiSemaphore);
    }
}

void digitclock_setMinute(uint8_t minu)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        // FUNCTION
        lv_label_set_text_fmt(label_clkminute, "%02d", minu);
        xSemaphoreGive(xGuiSemaphore);
    }
}

void digitclock_setSecond(uint8_t secd)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        // FUNCTION
        lv_label_set_text_fmt(label_clksecond, "%02d", secd);
        xSemaphoreGive(xGuiSemaphore);
    }
}

void digitclock_setDateStr(char* date)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        // FUNCTION
        lv_label_set_text_fmt(label_dateStr, "%s", date);
        xSemaphoreGive(xGuiSemaphore);
    }
}

void digitclock_setWeek(uint8_t week)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        // FUNCTION
        //lv_label_set_text_fmt(label_weekCNStr,"%s", "日");
        lv_label_set_text_fmt(label_weekCNStr, "%.*s",4, weekCNarray[week]);
        xSemaphoreGive(xGuiSemaphore);
    }
}

static void pannel_OvO_create(lv_obj_t* parent);
static void pannel_TempAndHumi_create(lv_obj_t* parent);
static void panel_DigitClock_create(lv_obj_t* parent);
static void panel_DateDis_create(lv_obj_t* parent);
static void pannel_logo_create(lv_obj_t* parent);

void screen_digitclock_create(lv_obj_t* parent)
{
    static lv_coord_t digitclock_column_dsc[] = { 75,75,75, LV_GRID_TEMPLATE_LAST };
    static lv_coord_t digitclock_row_dsc[] = { 2,80,90,50,2, LV_GRID_TEMPLATE_LAST };

    lv_obj_t* panel_OvO = lv_obj_create(parent);
    lv_obj_set_size(panel_OvO, 75, 50);
    lv_obj_add_style(panel_OvO, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_OvO, LV_OBJ_FLAG_SCROLLABLE);
    pannel_OvO_create(panel_OvO);

    lv_obj_t* panel_TempAndHumi = lv_obj_create(parent);
    lv_obj_set_size(panel_TempAndHumi, 150, 80);
    lv_obj_add_style(panel_TempAndHumi, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_TempAndHumi, LV_OBJ_FLAG_SCROLLABLE);
    pannel_TempAndHumi_create(panel_TempAndHumi);

    lv_obj_t* panel_DigitClock = lv_obj_create(parent);
    lv_obj_set_size(panel_DigitClock, 225, 90);
    lv_obj_add_style(panel_DigitClock, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_DigitClock, LV_OBJ_FLAG_SCROLLABLE);
    panel_DigitClock_create(panel_DigitClock);

    lv_obj_t* panel_DateDis = lv_obj_create(parent);
    lv_obj_set_size(panel_DateDis, 150, 50);
    lv_obj_add_style(panel_DateDis, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_DateDis, LV_OBJ_FLAG_SCROLLABLE);
    panel_DateDis_create(panel_DateDis);

    //lv_obj_t* panel_Week = lv_obj_create(parent);
    //lv_obj_set_size(panel_Week, 75, 50);
    //lv_obj_add_style(panel_Week, &style_pannel_block, 0);
    //lv_obj_clear_flag(panel_Week, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t* panel_logo = lv_obj_create(parent);
    lv_obj_set_size(panel_logo, 75, 80);
    lv_obj_add_style(panel_logo, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_logo, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(panel_logo, 5, 0);
    pannel_logo_create(panel_logo);

    lv_obj_set_grid_dsc_array(parent, digitclock_column_dsc, digitclock_row_dsc);

    lv_obj_set_grid_cell(panel_logo, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 1, 1);
    lv_obj_set_grid_cell(panel_TempAndHumi, LV_GRID_ALIGN_START, 1, 2, LV_GRID_ALIGN_START, 1, 1);
    lv_obj_set_grid_cell(panel_DigitClock, LV_GRID_ALIGN_CENTER, 0, 3, LV_GRID_ALIGN_CENTER, 2, 1);
    
    lv_obj_set_grid_cell(panel_DateDis, LV_GRID_ALIGN_START, 0, 2, LV_GRID_ALIGN_START, 3, 1);
    lv_obj_set_grid_cell(panel_OvO, LV_GRID_ALIGN_START, 2, 1, LV_GRID_ALIGN_START, 3, 1);
    //lv_obj_set_grid_cell(panel_Week, LV_GRID_ALIGN_START, 2, 1, LV_GRID_ALIGN_START, 3, 1);


    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_BETWEEN);
}

static void pannel_OvO_create(lv_obj_t* parent)
{
    lv_obj_set_style_bg_color(parent, lv_color_hex(0xFEDBD0), 0);

    label_QnQ = lv_label_create(parent);
    lv_label_set_text(label_QnQ, "X_X");
    lv_obj_set_size(label_QnQ, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_QnQ, &style_font_mediumLabel, 0);
    lv_obj_set_style_text_color(label_QnQ,lv_color_black(),0);
    lv_obj_align(label_QnQ, LV_ALIGN_CENTER, 0, 0);
}

static void pannel_TempAndHumi_create(lv_obj_t* parent)
{
    static lv_coord_t infoDisp_column_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(4),LV_GRID_FR(7),LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
    static lv_coord_t infoDisp_row_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(1) , LV_GRID_TEMPLATE_LAST };

    lv_obj_set_style_bg_color(parent, lv_color_hex(0x1976D2), 0);
    lv_obj_set_style_pad_all(parent, 5, 0);

    lv_obj_t* label_tempSymbol = lv_label_create(parent);
    lv_label_set_text_static(label_tempSymbol, "\xEF\x8B\x89");
    lv_obj_set_size(label_tempSymbol, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_tempSymbol, &style_font_awesomSymbol, 0);

    lv_obj_t* label_humiSymbol = lv_label_create(parent);
    lv_label_set_text_static(label_humiSymbol, "\xEF\x81\x83");
    lv_obj_set_size(label_humiSymbol, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_humiSymbol, &style_font_awesomSymbol, 0);

    lv_obj_t* label_tempTitle = lv_label_create(parent);
    lv_label_set_text_static(label_tempTitle, "温度:");
    lv_obj_set_size(label_tempTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_tempTitle, &style_frontTypeCN_smallLabel, 0);

    lv_obj_t* label_humiTitle = lv_label_create(parent);
    lv_label_set_text_static(label_humiTitle, "湿度:");
    lv_obj_set_size(label_humiTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_humiTitle, &style_frontTypeCN_smallLabel, 0);

    lv_obj_t* label_tempUnitName = lv_label_create(parent);
    lv_label_set_text_static(label_tempUnitName, "C");
    lv_obj_set_size(label_tempUnitName, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_tempUnitName, &style_font_smallLabel, 0);

    lv_obj_t* label_humiUnitName = lv_label_create(parent);
    lv_label_set_text_static(label_humiUnitName, "%");
    lv_obj_set_size(label_humiUnitName, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_humiUnitName, &style_font_smallLabel, 0);

    label_temperature = lv_label_create(parent);
    lv_label_set_text(label_temperature,"Error");
    lv_obj_set_size(label_temperature, lv_pct(50), LV_SIZE_CONTENT);
    lv_obj_add_style(label_temperature, &style_font_mediumLabel, 0);

    label_humidity = lv_label_create(parent);
    lv_label_set_text(label_humidity, "Error");
    lv_obj_set_size(label_humidity, lv_pct(50), LV_SIZE_CONTENT);
    lv_obj_add_style(label_humidity, &style_font_mediumLabel, 0);

    lv_obj_set_grid_dsc_array(parent, infoDisp_column_dsc, infoDisp_row_dsc);

    lv_obj_set_grid_cell(label_tempSymbol, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_tempTitle, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_temperature, LV_GRID_ALIGN_CENTER, 2, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_tempUnitName, LV_GRID_ALIGN_END, 3, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    lv_obj_set_grid_cell(label_humiSymbol, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_grid_cell(label_humiTitle, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_grid_cell(label_humidity, LV_GRID_ALIGN_CENTER, 2, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_grid_cell(label_humiUnitName, LV_GRID_ALIGN_END, 3, 1, LV_GRID_ALIGN_CENTER, 1, 1);

    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_EVENLY);
}

static void panel_DigitClock_create(lv_obj_t* parent)
{
    static lv_coord_t infoDisp_column_dsc[] = { LV_GRID_FR(1),20,LV_GRID_FR(1),20,LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
    static lv_coord_t infoDisp_row_dsc[] = { LV_GRID_FR(1) , LV_GRID_TEMPLATE_LAST };

    //lv_obj_set_style_bg_color(parent, lv_color_hex(0x3E2723), 0);
    lv_obj_set_style_bg_color(parent, lv_color_hex(0xFFA000), 0);
    lv_obj_set_style_pad_all(parent, 10, 0);

    lv_obj_t* label_hm = lv_label_create(parent);
    lv_label_set_text_static(label_hm, ":");
    lv_obj_set_size(label_hm, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_hm, &style_font_hugeLabel, 0);

    lv_obj_t* label_ms = lv_label_create(parent);
    lv_label_set_text_static(label_ms, ":");
    lv_obj_set_size(label_ms, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_ms, &style_font_hugeLabel, 0);

    label_clkhour = lv_label_create(parent);
    lv_label_set_text(label_clkhour, "Li");
    lv_obj_set_size(label_clkhour, lv_pct(25), LV_SIZE_CONTENT);
    lv_obj_add_style(label_clkhour, &style_font_hugeLabel, 0);

    label_clkminute = lv_label_create(parent);
    lv_label_set_text(label_clkminute, "Sr");
    lv_obj_set_size(label_clkminute, lv_pct(25), LV_SIZE_CONTENT);
    lv_obj_add_style(label_clkminute, &style_font_hugeLabel, 0);

    label_clksecond = lv_label_create(parent);
    lv_label_set_text(label_clksecond, "Rb");
    lv_obj_set_size(label_clksecond, lv_pct(25), LV_SIZE_CONTENT);
    lv_obj_add_style(label_clksecond, &style_font_hugeLabel, 0);

    lv_obj_set_grid_dsc_array(parent, infoDisp_column_dsc, infoDisp_row_dsc);

    lv_obj_set_grid_cell(label_clkhour, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_hm, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_clkminute, LV_GRID_ALIGN_START, 2, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_ms, LV_GRID_ALIGN_START, 3, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_clksecond, LV_GRID_ALIGN_START, 4, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_EVENLY);
}

static void panel_DateDis_create(lv_obj_t* parent)
{
    static lv_coord_t infoDisp_column_dsc[] = { LV_GRID_FR(3), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
    static lv_coord_t infoDisp_row_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(1) , LV_GRID_TEMPLATE_LAST };

    lv_obj_set_style_bg_color(parent, lv_color_hex(0xFFECB3), 0);
    lv_obj_set_style_pad_all(parent, 5, 0);


    label_dateStr = lv_label_create(parent);
    lv_label_set_text(label_dateStr, "1998/06/06");
    lv_obj_align(label_dateStr, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(label_dateStr, &style_font_smallLabel, 0);
    lv_obj_set_style_text_color(label_dateStr, lv_color_black(), 0);

    lv_obj_t* label_weekTitle = lv_label_create(parent);
    lv_label_set_text_static(label_weekTitle, "麋鹿的 星期");
    lv_obj_set_size(label_weekTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_weekTitle, &style_frontTypeCN_smallLabel, 0);
    //lv_obj_set_style_bg_color(label_weekTitle, lv_color_white(), 0); //测试
    //lv_obj_set_style_bg_opa(label_weekTitle, 200, 0);                //测试
    lv_obj_set_style_text_color(label_weekTitle, lv_color_black(), 0);

    label_weekCNStr = lv_label_create(parent);
    //淦，乃不知有汉
    lv_label_set_text(label_weekCNStr, "淦");//"日 一 二 三 四 五 六"
    lv_obj_align(label_weekCNStr, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(label_weekCNStr, &style_frontTypeCN_smallLabel, 0);
    //lv_obj_set_style_bg_color(label_weekCNStr, lv_color_white(), 0); //测试
    //lv_obj_set_style_bg_opa(label_weekCNStr, 200, 0);                //测试
    lv_obj_set_style_text_color(label_weekCNStr, lv_color_black(), 0);

    lv_obj_set_grid_dsc_array(parent, infoDisp_column_dsc, infoDisp_row_dsc);

    lv_obj_set_grid_cell(label_dateStr, LV_GRID_ALIGN_CENTER, 0, 2, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_weekTitle, LV_GRID_ALIGN_END, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_grid_cell(label_weekCNStr, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 1, 1);

    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_EVENLY);
}

static void pannel_logo_create(lv_obj_t* parent)
{
    //lv_obj_set_style_bg_color(parent, lv_color_hex(0x29B6F6), 0);
    //lv_obj_set_style_bg_opa(parent, 0, 0);

    lv_obj_t* img1 = lv_img_create(parent);
    LV_IMG_DECLARE(bellaIMG);
    lv_img_set_src(img1, &bellaIMG);
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
}
