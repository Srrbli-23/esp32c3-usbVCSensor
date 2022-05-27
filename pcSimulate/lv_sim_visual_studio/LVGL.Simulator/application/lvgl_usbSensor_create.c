#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_application_create.h"
#include "lvgl_usbSensor_create.h"

LV_IMG_DECLARE(dianaIMG);

static lv_obj_t* label_voltageNumb;
static lv_obj_t* label_currentNumb;
static lv_obj_t* label_wattNumb;
static lv_obj_t* label_ohmNumb;
static lv_obj_t* meter_chargeInfo;
static lv_meter_indicator_t* indic1;
static lv_meter_indicator_t* indic2;

static lv_anim_t anim_meterToChange;

static int8_t  anim_voltage_last = 0;
static int8_t  anim_current_last = 0;

static void anim_meterChargeInfo_cb(void* indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter_chargeInfo, (lv_meter_indicator_t*)indic, v);
}

static void pannel_VoltAndCurrInfo_Display(lv_obj_t* parent);
static void pannel_chargeProtocol_Display(lv_obj_t* parent);
static void pannel_PowAndResInfo_Display(lv_obj_t* parent);
static void pannel_logo_Display(lv_obj_t* parent);

/*-----------------
 *    Globle Function
 *----------------*/

#define VOLTAGE_MAX 40960
#define CURRENT_MAX 5416

void usbSensor_voltageNumber_set(int32_t voltage)
{
    uint32_t voltage_inte;
    uint32_t voltage_frac;
    if(voltage < 0)
    {
        voltage_inte = voltage / 1000;
        voltage_frac = (~(voltage-1)) % 1000;
        lv_label_set_text_fmt(label_voltageNumb, "%d.%03d", voltage_inte, voltage_frac);
    }
    else
    {
        voltage_inte = voltage / 1000;
        voltage_frac = voltage % 1000;
        lv_label_set_text_fmt(label_voltageNumb, "%d.%03d", voltage_inte, voltage_frac);
    }
    
    voltage_inte = voltage * 100 / VOLTAGE_MAX;
    lv_anim_set_values(&anim_meterToChange, anim_voltage_last, voltage_inte);

    lv_anim_set_var(&anim_meterToChange, indic1);
    lv_anim_start(&anim_meterToChange);
    anim_voltage_last = voltage_inte;
    return;
}

void usbSensor_currentNumber_set(int32_t ampele)
{
    int32_t current_inte;
    int32_t current_frac;
    if(ampele < 0)
    {
        current_inte = ampele / 1000;
        current_frac = (~(ampele - 1)) % 1000;
        lv_label_set_text_fmt(label_currentNumb, "%d.%03d", current_inte, current_frac);
    }
    else
    {
        current_inte = ampele / 1000;
        current_frac = ampele % 1000;
        lv_label_set_text_fmt(label_currentNumb, "%d.%03d", current_inte, current_frac);
    }
    

    current_inte = ampele * 100 / CURRENT_MAX;
    lv_anim_set_values(&anim_meterToChange, anim_current_last, current_inte);
    lv_anim_set_var(&anim_meterToChange, indic2);
    lv_anim_start(&anim_meterToChange);
    anim_current_last = current_inte;
    return;
}

void usbSensor_wattNumb_set(int32_t watt)
{
    if (watt < 0)
    {
        watt = ~(watt - 1);
    }
    int32_t watt_inte = watt / 10000;
    int32_t watt_frac = watt % 10000;
    lv_label_set_text_fmt(label_wattNumb, "%d.%04d", watt_inte, watt_frac);
    return;
}

void usbSensor_ohmNumb_set(int32_t ohm)
{
    int32_t ohm_inte;
    int32_t ohm_frac;
    if (ohm != 0)
    {
        if (ohm < 0)
        {
            ohm_inte = ohm / 100;
            ohm_frac = (~(ohm - 1)) % 100;
        }
        else
        {
            ohm_inte = ohm / 100;
            ohm_frac = ohm % 100;
        }
        lv_label_set_text_fmt(label_ohmNumb, "%d.%02d", ohm_inte, ohm_frac);
    }
    else
    {
        lv_label_set_text(label_ohmNumb, "inf");
    }
    
    return;
}

void screen_usbSensor_create(lv_obj_t* parent)
{
    static lv_coord_t usbSensor_column_dsc[] = {75,75,70, LV_GRID_TEMPLATE_LAST };
    static lv_coord_t usbSensor_row_dsc[]    = {2,75,75,70,2, LV_GRID_TEMPLATE_LAST };

    lv_obj_t* panel_ValtAndCurr = lv_obj_create(parent);
    lv_obj_set_size(panel_ValtAndCurr, 155, 155);
    lv_obj_add_style(panel_ValtAndCurr, &style_pannel_block,0);
    lv_obj_clear_flag(panel_ValtAndCurr, LV_OBJ_FLAG_SCROLLABLE);
    pannel_VoltAndCurrInfo_Display(panel_ValtAndCurr);

    lv_obj_t* panel_PowAndRes = lv_obj_create(parent);
    lv_obj_set_size(panel_PowAndRes, 230, 70);
    lv_obj_add_style(panel_PowAndRes, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_PowAndRes, LV_OBJ_FLAG_SCROLLABLE);
    pannel_PowAndResInfo_Display(panel_PowAndRes);

    lv_obj_t* panel_ProtolInfo = lv_obj_create(parent);
    lv_obj_set_size(panel_ProtolInfo, 70, 75);
    lv_obj_add_style(panel_ProtolInfo, &style_pannel_block, 0); //开启
    lv_obj_clear_flag(panel_ProtolInfo, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(panel_ProtolInfo, 5, 0);
    pannel_chargeProtocol_Display(panel_ProtolInfo);

    lv_obj_t* panel_logo = lv_obj_create(parent);
    lv_obj_set_size(panel_logo, 70, 75);
    lv_obj_add_style(panel_logo, &style_pannel_block, 0);  //开启
    lv_obj_clear_flag(panel_logo, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(panel_logo, 5, 0);
    pannel_logo_Display(panel_logo);

    lv_obj_set_grid_dsc_array(parent, usbSensor_column_dsc, usbSensor_row_dsc);
    lv_obj_set_grid_cell(panel_ValtAndCurr, LV_GRID_ALIGN_START, 0, 2, LV_GRID_ALIGN_START, 1, 2);
    lv_obj_set_grid_cell(panel_ProtolInfo, LV_GRID_ALIGN_START, 2, 1, LV_GRID_ALIGN_START, 1, 1);
    lv_obj_set_grid_cell(panel_logo, LV_GRID_ALIGN_START, 2, 1, LV_GRID_ALIGN_END, 2, 1);
    lv_obj_set_grid_cell(panel_PowAndRes, LV_GRID_ALIGN_START, 0, 3, LV_GRID_ALIGN_START, 3, 1);

    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_BETWEEN);
}

/*
 * local function
 */

static void pannel_VoltAndCurrInfo_Display(lv_obj_t* parent)
{
    static lv_coord_t infoDisp_column_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(4),5,20, LV_GRID_TEMPLATE_LAST };
    static lv_coord_t infoDisp_row_dsc[] = { 5,10,LV_GRID_FR(1),3 ,5,10,LV_GRID_FR(1) , LV_GRID_TEMPLATE_LAST };

    lv_obj_set_style_bg_color(parent, lv_color_hex(0xee6002), 0);

    label_voltageNumb = lv_label_create(parent);
    lv_label_set_text_fmt(label_voltageNumb, "%d.%d", 3, 315); // neet to be global
    lv_obj_set_size(label_voltageNumb, LV_SIZE_CONTENT, lv_pct(20));
    lv_obj_add_style(label_voltageNumb, &style_font_hugeLabel, 0);

    lv_obj_t* label_voltageUnitName = lv_label_create(parent);
    lv_label_set_text_static(label_voltageUnitName, "V");
    lv_obj_set_size(label_voltageUnitName, 20, LV_SIZE_CONTENT);
    lv_obj_add_style(label_voltageUnitName, &style_font_mediumLabel, 0);

    lv_obj_t* label_voltageCNTitle = lv_label_create(parent);
    lv_label_set_text_static(label_voltageCNTitle, "电压");
    lv_obj_set_size(label_voltageCNTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_voltageCNTitle, &style_frontTypeCN_smallLabel, 0);

    lv_obj_t* label_voltageENTitle = lv_label_create(parent);
    lv_label_set_text_static(label_voltageENTitle, "voltage");
    lv_obj_set_size(label_voltageENTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_voltageENTitle, &style_font_smallLabel, 0);

    lv_obj_t* label_voltageSymbol = lv_label_create(parent);
    lv_label_set_text_static(label_voltageSymbol, "\xEF\x83\xA7");
    lv_obj_set_size(label_voltageSymbol, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_voltageSymbol, &style_font_awesomSymbol, 0);

    //电流设置

    label_currentNumb = lv_label_create(parent);
    lv_label_set_text_fmt(label_currentNumb, "%d.%d", 1, 618); // neet to be global
    lv_obj_set_size(label_currentNumb, LV_SIZE_CONTENT, lv_pct(20));
    lv_obj_add_style(label_currentNumb, &style_font_hugeLabel, 0);

    lv_obj_t* label_currentUnitName = lv_label_create(parent);
    lv_label_set_text_static(label_currentUnitName, "A");
    lv_obj_set_size(label_currentUnitName, 20, LV_SIZE_CONTENT);
    lv_obj_add_style(label_currentUnitName, &style_font_mediumLabel, 0);

    lv_obj_t* label_currentCNTitle = lv_label_create(parent);
    lv_label_set_text_static(label_currentCNTitle, "电流");
    lv_obj_set_size(label_currentCNTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_currentCNTitle, &style_frontTypeCN_smallLabel, 0);

    lv_obj_t* label_currentENTitle = lv_label_create(parent);
    lv_label_set_text_static(label_currentENTitle, "current");
    lv_obj_set_size(label_currentENTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_currentENTitle, &style_font_smallLabel, 0);

    lv_obj_t* label_currentSymbol = lv_label_create(parent);
    lv_label_set_text_static(label_currentSymbol, "\xEF\xA0\xBE");
    lv_obj_set_size(label_currentSymbol, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_currentSymbol, &style_font_awesomSymbol, 0);

    lv_obj_set_grid_dsc_array(parent, infoDisp_column_dsc, infoDisp_row_dsc);
    //第一排
    lv_obj_set_grid_cell(label_voltageENTitle, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_grid_cell(label_voltageCNTitle, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_voltageUnitName, LV_GRID_ALIGN_END, 3, 1, LV_GRID_ALIGN_CENTER, 0, 2);
    lv_obj_set_grid_cell(label_voltageSymbol, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 2);

    //第二排
    lv_obj_set_grid_cell(label_voltageNumb, LV_GRID_ALIGN_CENTER, 0, 4, LV_GRID_ALIGN_CENTER, 2, 1);

    //第三排
    lv_obj_set_grid_cell(label_currentENTitle, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 5, 1);
    lv_obj_set_grid_cell(label_currentCNTitle, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 4, 1);
    lv_obj_set_grid_cell(label_currentUnitName, LV_GRID_ALIGN_END, 3, 1, LV_GRID_ALIGN_CENTER, 4, 2);
    lv_obj_set_grid_cell(label_currentSymbol, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 4, 2);

    //第四排
    lv_obj_set_grid_cell(label_currentNumb, LV_GRID_ALIGN_CENTER, 0, 4, LV_GRID_ALIGN_CENTER, 6, 1);

    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_START);
}

static void pannel_chargeProtocol_Display(lv_obj_t* parent)
{
#define PANNEL_CHARGEPROTOCOL_BG_COLOR_ lv_color_hex(0xffde03)
    
    lv_obj_set_style_bg_color(parent, PANNEL_CHARGEPROTOCOL_BG_COLOR_, 0);

    meter_chargeInfo = lv_meter_create(parent);
    lv_obj_center(meter_chargeInfo);
    lv_obj_set_size(meter_chargeInfo, 85, 85);
    lv_obj_remove_style(meter_chargeInfo, NULL, LV_PART_INDICATOR);

    lv_meter_scale_t* scale_chargeInfo = lv_meter_add_scale(meter_chargeInfo);
    lv_meter_set_scale_ticks(meter_chargeInfo, scale_chargeInfo, 11, 2, 20, PANNEL_CHARGEPROTOCOL_BG_COLOR_);
    lv_meter_set_scale_major_ticks(meter_chargeInfo, scale_chargeInfo, 10, 1, 10, lv_color_white(), -20);
    lv_meter_set_scale_range(meter_chargeInfo, scale_chargeInfo, 0, 100, 270, 135);
    lv_obj_set_style_border_width(meter_chargeInfo, 0, 0);
    lv_obj_set_style_bg_color(meter_chargeInfo, PANNEL_CHARGEPROTOCOL_BG_COLOR_, 0);

    indic1 = lv_meter_add_arc(meter_chargeInfo, scale_chargeInfo, 10, lv_palette_main(LV_PALETTE_RED), 0);
    //lv_meter_indicator_t* indic2 = lv_meter_add_arc(meter_chargeInfo, scale_chargeInfo, 10, lv_color_hex(0xf9aa33),-10);
    indic2 = lv_meter_add_arc(meter_chargeInfo, scale_chargeInfo, 5, lv_color_hex(0x442c2e), -10);

    lv_meter_set_indicator_end_value(meter_chargeInfo, indic1, 20);
    lv_meter_set_indicator_end_value(meter_chargeInfo, indic2, 100);

    lv_anim_init(&anim_meterToChange);
    lv_anim_set_time(&anim_meterToChange, 50);
    lv_anim_set_exec_cb(&anim_meterToChange, anim_meterChargeInfo_cb);
    lv_anim_set_values(&anim_meterToChange, 20, 80);

    lv_anim_set_var(&anim_meterToChange, indic1);

    lv_anim_set_early_apply(&anim_meterToChange, true);

    lv_anim_start(&anim_meterToChange);
    usbSensor_voltageNumber_set(12000);
}

static void pannel_PowAndResInfo_Display(lv_obj_t* parent)
{
    static lv_coord_t infoDisp_column_dsc[] = { LV_GRID_FR(2),LV_GRID_FR(5),LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
    static lv_coord_t infoDisp_row_dsc[] = { LV_GRID_FR(1), LV_GRID_FR(1),  LV_GRID_TEMPLATE_LAST };

    lv_obj_set_style_bg_color(parent, lv_color_hex(0x1565c0), 0);

    label_wattNumb = lv_label_create(parent);
    lv_label_set_text_fmt(label_wattNumb, "%d.%d", 10, 2514);
    lv_obj_add_style(label_wattNumb, &style_font_mediumLabel, 0);

    lv_obj_t* label_wattUnitName = lv_label_create(parent);
    lv_label_set_text_static(label_wattUnitName, "Watt");
    lv_obj_add_style(label_wattUnitName, &style_font_smallLabel, 0);

    lv_obj_t* label_wattTitle = lv_label_create(parent);
    lv_label_set_text_static(label_wattTitle, "功率 P:");
    lv_obj_add_style(label_wattTitle, &style_frontTypeCN_smallLabel, 0);

    //电阻设置

    label_ohmNumb = lv_label_create(parent);
    lv_label_set_text_fmt(label_ohmNumb, "%d.%d", 400, 21);
    lv_obj_add_style(label_ohmNumb, &style_font_mediumLabel, 0);

    lv_obj_t* label_ohmTitle = lv_label_create(parent);
    lv_label_set_text_static(label_ohmTitle, "电阻 R:");
    lv_obj_add_style(label_ohmTitle, &style_frontTypeCN_smallLabel, 0);

    lv_obj_t* label_ohmUnitName = lv_label_create(parent);
    lv_label_set_text_static(label_ohmUnitName, "Ohm");
    lv_obj_add_style(label_ohmUnitName, &style_font_smallLabel, 0);

    lv_obj_set_grid_dsc_array(parent, infoDisp_column_dsc, infoDisp_row_dsc);

    //第一排
    lv_obj_set_grid_cell(label_wattNumb, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_wattUnitName, LV_GRID_ALIGN_END, 2, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_wattTitle, LV_GRID_ALIGN_END, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    //第二排
    lv_obj_set_grid_cell(label_ohmNumb, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_grid_cell(label_ohmTitle, LV_GRID_ALIGN_END, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_grid_cell(label_ohmUnitName, LV_GRID_ALIGN_END, 2, 1, LV_GRID_ALIGN_CENTER, 1, 1);

    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_START);
}

static void pannel_logo_Display(lv_obj_t* parent)
{
    lv_obj_t* img1 = lv_img_create(parent);
    lv_img_set_src(img1, &dianaIMG);
    lv_obj_align(img1,LV_ALIGN_CENTER,0,0 );
}
