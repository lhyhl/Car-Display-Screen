// usrcode/car_data.h
#ifndef CAR_DATA_H
#define CAR_DATA_H

#include "../../lvgl/lvgl.h"

// 图片声明
LV_IMG_DECLARE(GT500);
LV_IMG_DECLARE(Mercedes);
LV_IMG_DECLARE(RollsRoyceHurricane);
LV_IMG_DECLARE(left);
LV_IMG_DECLARE(right);

// 汽车信息结构
typedef struct {
    const char *name;
    const lv_img_dsc_t *image;
    const char *description;
    const char *announcement;
    const char *discount_info;
    const char *gift_info;
} car_info_t;

// 外部声明
extern car_info_t cars[];
extern const int car_count;
extern int current_car_index;

// 函数声明
void update_car_display(void);
void update_announcement_info(void);

#endif