#ifndef CAR_DATA_H
#define CAR_DATA_H

#include "../../lvgl/lvgl.h"

// 图片声明

LV_IMG_DECLARE(left);                     // 声明向左箭头图片
LV_IMG_DECLARE(right);                    // 声明向右箭头图片
LV_IMG_DECLARE(Porsche911GT3);            // 声明保时捷911GT3图片
LV_IMG_DECLARE(McLaren600LT);             // 声明迈凯伦600LT图片  
LV_IMG_DECLARE(Ferrari812);               //声明法拉利812图片  



// 汽车信息结构体
typedef struct {
    const char *name;              // 汽车型号名称
    const lv_img_dsc_t *image;     // 指向LVGL图片描述符的指针
    const char *description;       // 汽车详细描述信息
    const char *announcement;      // 官方公告或新闻
    const char *discount_info;     // 折扣优惠信息
    const char *gift_info;         // 赠品信息
} car_info_t;

// 外部变量声明 - 这些变量在car_data.c中定义
extern car_info_t cars[];          // 汽车信息数组，包含所有车型数据
extern const int car_count;        // 汽车总数，用于数组边界检查
extern int current_car_index;      // 当前显示的汽车索引，用于轮播控制

// 函数声明 - 界面更新相关功能
void update_car_display(void);     // 更新主汽车显示（图片、名称、描述等）
void update_announcement_info(void); // 更新公告和优惠信息显示

#endif