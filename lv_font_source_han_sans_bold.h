#ifndef _LV_FONT_SOURCE_HAN_H
#define _LV_FONT_SOURCE_HAN_H

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

//申明下面的这些变量(每一个变量都对应各自的C文件)
//如果需要使用下面的哪种字体 需要编译相应的C文件 但会导致后面的demo文件很大

//20字体的大小。
// LV_FONT_DECLARE(lv_font_source_han_sans_bold_20);


//经过测试 这个也是20字体的大小 但它是粗体。
LV_FONT_DECLARE(chinese_ziku);


#endif
