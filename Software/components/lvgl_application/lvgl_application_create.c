#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_application_create.h"
#include "lvgl_usbSensor_create.h"
#include "lvgl_digitclock_create.h"
#include "lvgl_netInfo_create.h"


LV_FONT_DECLARE(lv_font_msYaHei);
LV_FONT_DECLARE(lv_font_awesom);

lv_style_t style_pannel_block;

lv_style_t style_font_smallLabel;
lv_style_t style_font_mediumLabel;
lv_style_t style_font_hugeLabel;
lv_style_t style_font_awesomSymbol;      // 图表字体 
lv_style_t style_frontTypeCN_smallLabel; //总体高19pix 字体大小8 基线4pix

lv_obj_t* tabview;


#ifndef CONFIG_APP_PROJECT_VER
static lv_obj_t* outShapeGen_create(lv_obj_t* parent)
{
    //辅助函数
    lv_obj_t* pannel_outShape = lv_obj_create(parent);
    lv_obj_set_size(pannel_outShape, 280, 240);
    lv_obj_set_style_radius(pannel_outShape, 40, 0);
    //lv_obj_set_style_opa(pannel_outShape, 0, 0);
    lv_obj_set_style_bg_opa(pannel_outShape, 0, 0);
    lv_obj_set_style_border_width(pannel_outShape, 1, 0);
    lv_obj_set_style_border_color(pannel_outShape, lv_color_hex(0x00000), 0);

    return pannel_outShape;
}
#endif

/*-----------------
 *    Globle Function
 *----------------*/
void lvgl_application_main_create(void)
{
    lv_style_init(&style_pannel_block);
    lv_style_set_radius(&style_pannel_block, 20);
    lv_style_set_border_width(&style_pannel_block, 0);

    lv_style_init(&style_font_smallLabel);
    lv_style_set_text_font(&style_font_smallLabel, &lv_font_montserrat_14);
    lv_style_set_text_color(&style_font_smallLabel, lv_color_white());

    lv_style_init(&style_font_mediumLabel);
    lv_style_set_text_font(&style_font_mediumLabel, &lv_font_montserrat_22);
    lv_style_set_text_color(&style_font_mediumLabel, lv_color_white());

    lv_style_init(&style_font_hugeLabel);
    lv_style_set_text_font(&style_font_hugeLabel, &lv_font_montserrat_32);
    lv_style_set_text_color(&style_font_hugeLabel, lv_color_white());

    lv_style_init(&style_frontTypeCN_smallLabel);
    lv_style_set_text_font(&style_frontTypeCN_smallLabel, &lv_font_msYaHei);
    lv_style_set_text_color(&style_frontTypeCN_smallLabel, lv_color_white());

    lv_style_init(&style_font_awesomSymbol);
    lv_style_set_text_font(&style_font_awesomSymbol, &lv_font_awesom);
    lv_style_set_text_color(&style_font_awesomSymbol, lv_color_white());

    // 方案一
#define APP_TABVIEW_BG_COLOR lv_color_black()
#define APP_TABVIEW_FONT_COLOR lv_color_white()

    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 40);
    lv_obj_t* tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_bg_color(tab_btns, lv_color_hex(0x42A5F5), 0);
    lv_obj_set_style_bg_color(tab_btns, APP_TABVIEW_BG_COLOR, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(tab_btns, 255, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(tab_btns, APP_TABVIEW_FONT_COLOR, 0);
    lv_obj_set_style_text_color(tab_btns, APP_TABVIEW_FONT_COLOR, LV_PART_ITEMS | LV_STATE_CHECKED);
    //lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_NONE, LV_PART_ITEMS | LV_STATE_CHECKED);


    lv_obj_t* tab1 = lv_tabview_add_tab(tabview, "usb");
    lv_obj_set_size(tab1, 240, 240);
    lv_obj_clear_flag(tab1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(tab1, 0, 0);
    lv_obj_set_style_bg_color(tab1, APP_TABVIEW_BG_COLOR, 0);
    lv_obj_set_style_bg_opa(tab1, LV_OPA_COVER, 0);

    lv_obj_t* tab2 = lv_tabview_add_tab(tabview, "clk");
    lv_obj_set_size(tab2, 240, 240);
    lv_obj_clear_flag(tab2, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(tab2, 0, 0);
    lv_obj_set_style_bg_color(tab2, APP_TABVIEW_BG_COLOR, 0);
    lv_obj_set_style_bg_opa(tab2, LV_OPA_COVER, 0);

    lv_obj_t* tab3 = lv_tabview_add_tab(tabview, "net");
    lv_obj_set_size(tab3, 240, 240);
    lv_obj_clear_flag(tab3, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(tab3, 0, 0);
    lv_obj_set_style_bg_color(tab3, APP_TABVIEW_BG_COLOR, 0);
    lv_obj_set_style_bg_opa(tab3, LV_OPA_COVER, 0);

    screen_usbSensor_create(tab1);
    screen_digitclock_create(tab2);
    screen_networkInfo_create(tab3);

    lv_tabview_set_act(tabview, 2, LV_ANIM_ON);

#ifndef CONFIG_APP_PROJECT_VER
    lv_obj_t* src_now = outShapeGen_create(lv_scr_act()); //WINDOWSimulate ONLY
    lv_obj_move_foreground(tabview); //如果需要测试屏幕，请注释这里
#endif
}
