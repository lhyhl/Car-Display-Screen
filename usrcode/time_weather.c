// usrcode/time_weather.c
#include "inc/time_weather.h"
#include "inc/ui.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// 广告轮播相关变量
uint8_t ad_index = 0;  // 当前广告索引，用于轮播
// 广告内容数组，包含4条不同的广告文本
const char *ads[] = {
    "限时优惠:购车享0首付",     // 广告1：金融优惠
    "全系车型火热销售中",       // 广告2：销售宣传
    "免费保养服务正在进行",     // 广告3：售后服务
    "年度最佳汽车经销商"        // 广告4：荣誉展示
};

/**
 * @brief 更新时间显示
 * 获取系统时间并格式化为中文显示格式，更新到时间标签
 * @param time_label 要更新时间显示的LVGL标签对象
 */
void update_time(lv_obj_t *time_label)
{
    static char display_str[100];  // 静态字符数组，用于存储格式化后的时间字符串
    
    // 获取当前系统时间
    time_t now = time(NULL);
    
    // 检查时间获取是否失败（time函数返回-1表示失败）
    if (now == (time_t)-1) {
        lv_label_set_text(time_label, "时间获取失败");  // 设置错误提示文本
        return;  // 退出函数
    }
    
    // 将时间转换为本地时间结构体（包含年、月、日、时、分、秒等信息）
    struct tm *t = localtime(&now);
    if (t == NULL) {
        lv_label_set_text(time_label, "时间格式错误");  // 设置错误提示文本
        return;  // 退出函数
    }

    
    // 格式化时间字符串：
    // %02d:%02d:%02d        
    // %04d年%02d月%02d日    
    snprintf(display_str, sizeof(display_str), 
             "%02d:%02d:%02d\n%04d年%02d月%02d日", 
             t->tm_hour,      // 小时（0-23）
             t->tm_min,       // 分钟（0-59）
             t->tm_sec,       // 秒（0-59）
             t->tm_year + 1900, // 年份（tm_year是从1900年开始的偏移量）
             t->tm_mon + 1,   // 月份（0-11，所以需要+1）
             t->tm_mday       // 日期（1-31）
                    );  

    // 将格式化后的时间字符串设置到LVGL标签
    lv_label_set_text(time_label, display_str);
}

/**
 * @brief 更新天气信息
 * 模拟天气数据更新，根据时间变化显示不同的天气状况
 * @param weather_label 要更新天气显示的LVGL标签对象
 */
void update_weather(lv_obj_t *weather_label)
{
    // 天气状况数组，包含4种基本的天气类型
    const char *weather_conditions[] = {"晴", "多云", "雨", "阴"};
    
    // 获取当前系统时间
    time_t now = time(NULL);
    // 如果时间获取失败，显示默认天气信息
    if(now == (time_t)-1) {
        lv_label_set_text(weather_label, "25度 晴");  // 默认天气：25度晴天
        return;  // 退出函数
    }

    // 转换为本地时间结构体
    struct tm *t = localtime(&now);
    if(t == NULL) {
        lv_label_set_text(weather_label, "25度 晴");  // 默认天气：25度晴天
        return;  // 退出函数
    }

    // 根据小时计算天气索引，实现天气随时间变化：
    // 每6分钟切换一次天气类型，总共4种天气类型循环
    int weather_index = (t->tm_min / 6) % 4;
    
    // 模拟温度变化：基础温度20度 + 小时数的个位数
    // 这样温度会在20-29度之间变化
    int temp = 20 + (t->tm_min % 10);

    // 格式化天气字符串
    char weather_str[30];
    snprintf(weather_str, sizeof(weather_str), "%d度 %s", temp, weather_conditions[weather_index]);

    // 更新天气标签显示
    lv_label_set_text(weather_label, weather_str);
}

/**
 * @brief 更新广告信息
 * 轮播显示广告内容，每次调用显示下一条广告
 * @param ad_label 要更新广告内容的LVGL标签对象
 */
void update_advertisement(lv_obj_t *ad_label)
{
    // 设置当前广告索引对应的广告文本
    lv_label_set_text(ad_label, ads[ad_index]);
    
    // 更新广告索引，实现轮播效果：
    // 当前索引+1，然后对4取模，确保索引在0-3之间循环
    ad_index = (ad_index + 1) % 4;
}

/**
 * @brief 时间更新定时器回调函数
 * LVGL定时器回调，定期更新时间显示
 * @param timer LVGL定时器对象指针
 */
void timer_callback(lv_timer_t *timer)
{
    // 调用更新时间函数，传入全局UI结构体中的时间标签
    update_time(ui.time_label);
}

/**
 * @brief 广告轮播定时器回调函数
 * LVGL定时器回调，定期轮播广告内容
 * @param timer LVGL定时器对象指针
 */
void ad_timer_callback(lv_timer_t *timer)
{
    // 调用更新广告函数，传入全局UI结构体中的广告标签
    update_advertisement(ui.ad_label);
}

/**
 * @brief 天气更新定时器回调函数
 * LVGL定时器回调，定期更新天气信息
 * @param timer LVGL定时器对象指针
 */
void weather_timer_callback(lv_timer_t *timer)
{
    // 调用更新天气函数，传入全局UI结构体中的天气标签
    update_weather(ui.weather_label);
}