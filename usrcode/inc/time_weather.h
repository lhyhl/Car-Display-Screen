// usrcode/time_weather.h
#ifndef TIME_WEATHER_H
#define TIME_WEATHER_H

#include "../../lvgl/lvgl.h"

// 广告相关
extern uint8_t ad_index;
extern const char *ads[];

// 函数声明
void update_time(lv_obj_t *time_label);
void update_weather(lv_obj_t *weather_label);
void update_advertisement(lv_obj_t *ad_label);
void timer_callback(lv_timer_t *timer);
void ad_timer_callback(lv_timer_t *timer);
void weather_timer_callback(lv_timer_t *timer);

#endif