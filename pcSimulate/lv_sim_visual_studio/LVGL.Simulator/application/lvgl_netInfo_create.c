#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "base64.h"

#include "lvgl_application_create.h"
#include "lvgl_netInfo_create.h"

static lv_obj_t* label_wifiStatus;
static lv_obj_t* label_ssidNameStr;

static lv_obj_t* label_ipAddrStr;
static lv_obj_t* label_ipMaskStr;
static lv_obj_t* label_ipGatewayStr;

static lv_obj_t* label_mqttStatus;

static void pannel_wifiInfo_create(lv_obj_t* parent);
static void pannel_ipAdmInfo_create(lv_obj_t* parent);
static void pannel_mqttClientInfo_create(lv_obj_t* parent);
static void pannel_macIDInfo_create(lv_obj_t* parent);
static void mac2base64str(uint8_t* mac,uint8_t* base64_out);
static void pannel_espTouchInfo_create(lv_obj_t* parent);

void networkInfo_wifiInfoStatus_set(char* str_WIFIstatus)
{
    //重新设置wifi 状态
    lv_label_set_text_fmt(label_wifiStatus,"%s",str_WIFIstatus);
}

void networkInfo_wifiInfoSSID_set(char* str_WIFIname)
{
    //重新设置wifi 状态
    lv_label_set_text_fmt(label_ssidNameStr,"%s",str_WIFIname);
}

void networkInfo_ipAdmInfo_set(char* ipaddress,char* ipmask,char* gateway)
{
    lv_label_set_text_fmt(label_ipAddrStr,"%d,%d,%d,%d",ipaddress[0],ipaddress[1],ipaddress[2],ipaddress[3]);
    lv_label_set_text_fmt(label_ipMaskStr,"%d,%d,%d,%d",ipmask[0],ipmask[1],ipmask[2],ipmask[3]);
    lv_label_set_text_fmt(label_ipGatewayStr,"%d,%d,%d,%d",gateway[0],gateway[1],gateway[2],gateway[3]);
}

void networkInfo_mqttClientInfo_set(char* str_MQTTstatus)
{
    lv_label_set_text_fmt(label_mqttStatus,"%s",str_MQTTstatus);
}

void screen_networkInfo_create(lv_obj_t* parent)
{
    static lv_coord_t networkInfo_column_dsc[] = { 60,55,40,75, LV_GRID_TEMPLATE_LAST };
    static lv_coord_t networkInfo_row_dsc[] = { 3,75,75,75,3, LV_GRID_TEMPLATE_LAST };

    lv_obj_t* panel_wifiInfo = lv_obj_create(parent);
    lv_obj_set_size(panel_wifiInfo, 155, 75);
    lv_obj_add_style(panel_wifiInfo, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_wifiInfo, LV_OBJ_FLAG_SCROLLABLE);
    pannel_wifiInfo_create(panel_wifiInfo);

    lv_obj_t* panel_espTouchInfo = lv_obj_create(parent);
    lv_obj_set_size(panel_espTouchInfo, 75, 75);
    lv_obj_add_style(panel_espTouchInfo, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_espTouchInfo, LV_OBJ_FLAG_SCROLLABLE);
    pannel_espTouchInfo_create(panel_espTouchInfo);

    lv_obj_t* panel_ipAdmInfo = lv_obj_create(parent);
    lv_obj_set_size(panel_ipAdmInfo, 115, 150);
    lv_obj_add_style(panel_ipAdmInfo, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_ipAdmInfo, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(panel_ipAdmInfo, 5, 0);
    pannel_ipAdmInfo_create(panel_ipAdmInfo);

    lv_obj_t* panel_mqttClientInfo = lv_obj_create(parent);
    lv_obj_set_size(panel_mqttClientInfo, 115, 75);
    lv_obj_add_style(panel_mqttClientInfo, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_mqttClientInfo, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(panel_mqttClientInfo, 5, 0);
    pannel_mqttClientInfo_create(panel_mqttClientInfo);

    lv_obj_t* panel_macIDInfo = lv_obj_create(parent);
    lv_obj_set_size(panel_macIDInfo, 115, 75);
    lv_obj_add_style(panel_macIDInfo, &style_pannel_block, 0);
    lv_obj_clear_flag(panel_macIDInfo, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(panel_macIDInfo, 5, 0);
    pannel_macIDInfo_create(panel_macIDInfo);

    lv_obj_set_grid_dsc_array(parent, networkInfo_column_dsc, networkInfo_row_dsc);
    lv_obj_set_grid_cell(panel_wifiInfo, LV_GRID_ALIGN_START, 0, 3, LV_GRID_ALIGN_START, 1, 1);
    lv_obj_set_grid_cell(panel_espTouchInfo, LV_GRID_ALIGN_START, 3, 1, LV_GRID_ALIGN_START, 1, 1);
    lv_obj_set_grid_cell(panel_ipAdmInfo, LV_GRID_ALIGN_START, 0, 2, LV_GRID_ALIGN_START, 2, 2);
    lv_obj_set_grid_cell(panel_mqttClientInfo, LV_GRID_ALIGN_START, 2, 2, LV_GRID_ALIGN_START, 2, 2);
    lv_obj_set_grid_cell(panel_macIDInfo, LV_GRID_ALIGN_START, 2, 2, LV_GRID_ALIGN_START, 3, 2);

    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_BETWEEN);
}

static void pannel_wifiInfo_create(lv_obj_t* parent)
{
    static lv_coord_t infoDisp_column_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(4), LV_GRID_TEMPLATE_LAST };
    static lv_coord_t infoDisp_row_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(1) , LV_GRID_TEMPLATE_LAST };

    lv_obj_set_style_bg_color(parent, lv_color_hex(0x00695C), 0);

    lv_obj_t* label_wifiTitle = lv_label_create(parent);
    lv_label_set_text_static(label_wifiTitle, "wifi");
    lv_obj_set_size(label_wifiTitle, LV_SIZE_CONTENT, 35);
    lv_obj_add_style(label_wifiTitle, &style_font_smallLabel, 0);

    label_wifiStatus = lv_label_create(parent);
    lv_label_set_text(label_wifiStatus, "Failed");
    lv_obj_set_size(label_wifiStatus, LV_SIZE_CONTENT, 35);
    lv_obj_add_style(label_wifiStatus, &style_font_smallLabel, 0);

    label_ssidNameStr = lv_label_create(parent);
    lv_label_set_text(label_ssidNameStr, "Failed");
    lv_obj_set_size(label_ssidNameStr, LV_SIZE_CONTENT, 35);
    lv_obj_add_style(label_ssidNameStr, &style_font_smallLabel, 0);

    networkInfo_wifiInfoStatus_set("disable");
    networkInfo_wifiInfoSSID_set("Unkonw");

    lv_obj_set_grid_dsc_array(parent, infoDisp_column_dsc, infoDisp_row_dsc);
    lv_obj_set_grid_cell(label_wifiTitle, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_wifiStatus, LV_GRID_ALIGN_END, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_ssidNameStr, LV_GRID_ALIGN_CENTER, 0, 2, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_EVENLY);
}

static void pannel_espTouchInfo_create(lv_obj_t* parent)
{
    //有空再写  先水个比赛
    lv_obj_set_style_bg_color(parent, lv_color_hex(0xC0CA33), 0);
    lv_obj_set_style_pad_all(parent, 5, 0);

    lv_obj_t* label_slogan = lv_label_create(parent);
    lv_label_set_text_static(label_slogan, "追光者参赛作品");
    lv_obj_add_style(label_slogan, &style_frontTypeCN_smallLabel, 0);
    lv_obj_set_size(label_slogan, lv_pct(80), lv_pct(80));
    lv_obj_center(label_slogan);
}

static void pannel_ipAdmInfo_create(lv_obj_t* parent)
{
    static lv_coord_t infoDisp_column_dsc[] = { LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
    static lv_coord_t infoDisp_row_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(1),LV_GRID_FR(1),LV_GRID_FR(1),LV_GRID_FR(1),LV_GRID_FR(1) , LV_GRID_TEMPLATE_LAST };

    lv_obj_set_style_bg_color(parent, lv_color_hex(0x0277BD), 0);

    lv_obj_t* label_ipAddrTitle = lv_label_create(parent);
    lv_label_set_text_static(label_ipAddrTitle, "ip address:");
    lv_obj_add_style(label_ipAddrTitle, &style_font_smallLabel, 0);

    label_ipAddrStr = lv_label_create(parent);
    lv_label_set_text(label_ipAddrStr, "xxx");
    lv_obj_add_style(label_ipAddrStr, &style_font_smallLabel, 0);

    lv_obj_t* label_ipMaskTitle = lv_label_create(parent);
    lv_label_set_text_static(label_ipMaskTitle, "ip mask:");
    lv_obj_add_style(label_ipMaskTitle, &style_font_smallLabel, 0);

    label_ipMaskStr = lv_label_create(parent);
    lv_label_set_text(label_ipMaskStr, "xxx");
    lv_obj_add_style(label_ipMaskStr, &style_font_smallLabel, 0);

    lv_obj_t* label_ipGatewayTitle = lv_label_create(parent);
    lv_label_set_text_static(label_ipGatewayTitle, "ip Gateway:");
    lv_obj_add_style(label_ipGatewayTitle, &style_font_smallLabel, 0);

    label_ipGatewayStr = lv_label_create(parent);
    lv_label_set_text(label_ipGatewayStr, "xxx");
    lv_obj_add_style(label_ipGatewayStr, &style_font_smallLabel, 0);

    lv_obj_set_grid_dsc_array(parent, infoDisp_column_dsc, infoDisp_row_dsc);
    lv_obj_set_grid_cell(label_ipAddrTitle, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_ipAddrStr, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_grid_cell(label_ipMaskTitle, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 2, 1);
    lv_obj_set_grid_cell(label_ipMaskStr, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 3, 1);
    lv_obj_set_grid_cell(label_ipGatewayTitle, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 4, 1);
    lv_obj_set_grid_cell(label_ipGatewayStr, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 5, 1);

    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_EVENLY);
}

static void pannel_mqttClientInfo_create(lv_obj_t* parent)
{
    static lv_coord_t infoDisp_column_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(3), LV_GRID_TEMPLATE_LAST };
    static lv_coord_t infoDisp_row_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };

    lv_obj_set_style_bg_color(parent, lv_color_hex(0x7E57C2), 0);

    lv_obj_t* label_mqttClientTitle = lv_label_create(parent);
    lv_label_set_text_static(label_mqttClientTitle, "mqtt:");
    lv_obj_add_style(label_mqttClientTitle, &style_font_smallLabel, 0);

    label_mqttStatus = lv_label_create(parent);
    lv_label_set_text(label_mqttStatus, "Failed");
    lv_obj_add_style(label_mqttStatus, &style_font_smallLabel, 0);

    lv_obj_t* label_mqttBrokerURI = lv_label_create(parent);
    lv_label_set_text_static(label_mqttBrokerURI, "lisrrb23.icu");
    lv_obj_add_style(label_mqttBrokerURI, &style_font_smallLabel, 0);

    lv_obj_set_grid_dsc_array(parent, infoDisp_column_dsc, infoDisp_row_dsc);
    lv_obj_set_grid_cell(label_mqttClientTitle, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_mqttStatus, LV_GRID_ALIGN_END, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_mqttBrokerURI, LV_GRID_ALIGN_CENTER, 0, 2, LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_EVENLY);
}

static void pannel_macIDInfo_create(lv_obj_t* parent)
{
    static lv_coord_t infoDisp_column_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
    static lv_coord_t infoDisp_row_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };

#ifndef CONFIG_APP_PROJECT_VER
    uint8_t mac_array[6] = { 0x2a, 0x65, 0xfb, 0xaa, 0x37, 0x94 };
    uint8_t mac_base64[9] = { 0 };
    mac2base64str(mac_array, mac_base64);
#else
    esp_mac_type_t mac_type = ESP_MAC_WIFI_STA;
    uint8_t mac_array[6] = {0};
    uint8_t mac_base64[9] = {0};
    esp_read_mac(mac_array,mac_type);
    mac2base64str(mac_array,mac_base64);
#endif

    lv_obj_set_style_bg_color(parent, lv_color_hex(0xBF360C), 0);

    lv_obj_t* label_macTitle = lv_label_create(parent);
    lv_label_set_text_static(label_macTitle, "mac:");
    lv_obj_add_style(label_macTitle, &style_font_smallLabel, 0);

    lv_obj_t* label_macEsp32c3Str = lv_label_create(parent);
    //lv_label_set_text_static(label_macEsp32c3Str, "fae3401bc289");
    lv_label_set_text_fmt(label_macEsp32c3Str, "%s",mac_base64);
    lv_obj_add_style(label_macEsp32c3Str, &style_font_smallLabel, 0);

    //屏幕太小放不下了，淦
    //lv_obj_t* label_idTitle = lv_label_create(parent);
    //lv_label_set_text_static(label_idTitle, "mqttID:");
    //lv_obj_add_style(label_idTitle, &style_font_smallLabel, 0);

    //lv_obj_t* label_idEsp32c3Str = lv_label_create(parent);
    //lv_label_set_text_static(label_idEsp32c3Str, "bdqa");
    //lv_obj_add_style(label_idEsp32c3Str, &style_font_smallLabel, 0);

    lv_obj_set_grid_dsc_array(parent, infoDisp_column_dsc, infoDisp_row_dsc);
    lv_obj_set_grid_cell(label_macTitle, LV_GRID_ALIGN_START, 0, 2, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(label_macEsp32c3Str, LV_GRID_ALIGN_CENTER, 0, 2, LV_GRID_ALIGN_CENTER, 1, 1);
    //lv_obj_set_grid_cell(label_idTitle, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    //lv_obj_set_grid_cell(label_idEsp32c3Str, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 1, 1);

    lv_obj_set_grid_align(parent, LV_GRID_ALIGN_SPACE_EVENLY, LV_GRID_ALIGN_SPACE_EVENLY);
}

static void mac2base64str(uint8_t* mac,uint8_t* base64_out)
{
    uint8_t buf[8];
    buf[0] = (mac[0] & 0xfc) >> 2;
    buf[1] = ((mac[0] & 0x03) << 4) + ((mac[1] & 0xf0) >> 4);
    buf[2] = ((mac[1] & 0x0f) << 2) + ((mac[2] & 0xc0) >> 6);
    buf[3] = mac[2] & 0x3f;

    buf[4] = (mac[3] & 0xfc) >> 2;
    buf[5] = ((mac[3] & 0x03) << 4) + ((mac[4] & 0xf0) >> 4);
    buf[6] = ((mac[4] & 0x0f) << 2) + ((mac[5] & 0xc0) >> 6);
    buf[7] = mac[5] & 0x3f;

    base64_out[0] = b64_table[buf[0]];
    base64_out[1] = b64_table[buf[1]];
    base64_out[2] = b64_table[buf[2]];
    base64_out[3] = b64_table[buf[3]];
    base64_out[4] = b64_table[buf[4]];
    base64_out[5] = b64_table[buf[5]];
    base64_out[6] = b64_table[buf[6]];
    base64_out[7] = b64_table[buf[7]];
    return;
}
