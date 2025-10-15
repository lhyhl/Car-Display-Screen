// usrcode/usr_code.h
#ifndef USR_CODE_H
#define USR_CODE_H

#include "../../lvgl/lvgl.h"
#include <time.h>

// 屏幕尺寸定义
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480

// 颜色定义
#define BG_COLOR           lv_color_hex(0x1a1a2e)   //深蓝色
#define TEXT_COLOR         lv_color_hex(0xffffff)   //纯白色
#define ACCENT_COLOR       lv_color_hex(0xe94560)   //鲜红色
#define SECONDARY_COLOR    lv_color_hex(0x0f3460)   //中蓝色

// 定义统一的尺寸和间距
#define BOX_WIDTH 220      // 文本框宽度
#define BOX_HEIGHT 80      // 文本框高度
#define BOX_SPACING 15     // 文本框间距
#define BOX_START_Y -110   // 起始Y坐标
// 字体声明
LV_FONT_DECLARE(chinese_ziku);
LV_FONT_DECLARE(lv_font_source_han_sans_bold_20);

// 结构体定义
typedef struct {
    lv_obj_t *screen;
    lv_obj_t *time_label;
    lv_obj_t *weather_label;
    lv_obj_t *announcement_label;
    lv_obj_t *discount_label;
    lv_obj_t *gift_label;
    lv_obj_t *ad_label;
    lv_obj_t *car_img;
    lv_obj_t *prev_btn;
    lv_obj_t *next_btn;
    lv_obj_t *car_name_label;
    lv_obj_t *detail_btn;
} display_ui_t;

// 全局UI实例声明
extern display_ui_t ui;

// 函数声明
void create_ui(display_ui_t *ui);
void detail_btn_callback(lv_event_t *e);
void prev_car_callback(lv_event_t *e);
void next_car_callback(lv_event_t *e);

#endif