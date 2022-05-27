
#ifndef LVGL_APPLICATION_CREATE_H_
#define LVGL_APPLICATION_CREATE_H_

#define MAX_TABVIEW_OBJ_NUMB 3

extern lv_style_t style_pannel_block;
extern lv_style_t style_font_smallLabel;
extern lv_style_t style_font_mediumLabel;
extern lv_style_t style_font_hugeLabel;
extern lv_style_t style_font_awesomSymbol;      // 图表字体 
extern lv_style_t style_frontTypeCN_smallLabel; //总体高19pix 字体大小8 基线4pix

extern lv_obj_t* tabview;

extern void lvgl_application_main_create(void);

#endif
