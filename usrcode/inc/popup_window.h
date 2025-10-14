// usrcode/popup_window.h
#ifndef POPUP_WINDOW_H
#define POPUP_WINDOW_H

#include "../../lvgl/lvgl.h"
#include "car_data.h"

// 函数声明
void show_car_detail_popup(int car_index);
void close_popup_callback(lv_event_t *e);

#endif