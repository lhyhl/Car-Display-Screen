// main.c
#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "usrcode/inc/ui.h"
#include "usrcode/inc/time_weather.h"


#define DISP_BUF_SIZE (800 * 480 / 10)

int main(void)
{
    // 初始化系统时间（如果需要）
    struct timeval tv;

    if(gettimeofday(&tv, NULL) == 0) { // 第二个参数传 NULL
        printf("系统时间初始化成功\n");
        printf("当前时间戳: %ld\n", tv.tv_sec);
    } else {
        printf("系统时间初始化失败\n");
    }

    // 设置时区
    setenv("TZ", "CST-8", 1); // 设置为中国标准时间
    tzset();
    /* 初始化 LVGL 核心库 */
    lv_init();

    /* 初始化 Linux Framebuffer 显示设备 */
    fbdev_init();

    /* 分配 LVGL 显示缓冲区 */
    static lv_color_t buf[DISP_BUF_SIZE];

    /* 初始化显示缓冲区描述符 */
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /* 初始化并注册显示驱动 */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res  = 800;
    disp_drv.ver_res  = 480;
    lv_disp_drv_register(&disp_drv);

    /* 初始化输入设备 */
    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1);
    indev_drv_1.type         = LV_INDEV_TYPE_POINTER;
    indev_drv_1.read_cb      = evdev_read;
    lv_indev_t * mouse_indev = lv_indev_drv_register(&indev_drv_1);

    /* 设置鼠标指针图标 */
    LV_IMG_DECLARE(mouse_cursor_icon)
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act());
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);
    lv_indev_set_cursor(mouse_indev, cursor_obj);

    // 创建主屏幕
    ui.screen = lv_scr_act();
    lv_obj_set_style_bg_color(ui.screen, BG_COLOR, 0);

    // 创建UI界面
    create_ui(&ui);

    // 创建定时器
    // main.c - 在创建定时器部分
    lv_timer_t * timer         = lv_timer_create(timer_callback, 1000, NULL);         // 1秒更新时间
    lv_timer_t * ad_timer      = lv_timer_create(ad_timer_callback, 5000, NULL);      // 5秒轮播广告
    lv_timer_t * weather_timer = lv_timer_create(weather_timer_callback, 8000, NULL); // 30秒更新天气  // 10秒更新天气
    /* LVGL 主循环 */
    while(1) {
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}

/* 系统 Tick 获取函数 */
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}