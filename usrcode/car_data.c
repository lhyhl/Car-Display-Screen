/**
 * @file car_data.c
 * @brief 汽车数据管理模块
 *
 * 该模块负责管理汽车展示相关的数据，包括汽车基本信息、图片资源、
 * 公告信息等，并提供数据更新接口。
 */

#include "inc/car_data.h"
#include "inc/ui.h"

// 汽车数据数组
car_info_t cars[] = {{"法拉利 812", &Ferrari812,
                      "法拉利 812\n\n"
                      "发动机:6.5L V12自然吸气\n"
                      "最大功率:800马力\n"
                      "0-100km/h:2.9秒\n"
                      "变速箱:7速双离合\n"
                      "驱动方式:后轮驱动\n"
                      "价格:¥5,300,000起",
                      "Superfast限量版", "专属定制方案", "赠送赛道体验日"},
                     {"保时捷 911 GT3", &Porsche911GT3,
                      "保时捷 911 GT3\n\n"
                      "发动机:4.0L 水平对置6缸\n"
                      "最大功率:510马力\n"
                      "0-100km/h:3.4秒\n"
                      "变速箱:7速PDK/6速手动\n"
                      "驱动方式:后轮驱动\n"
                      "价格:¥2,028,000起",
                      "全新911 GT3到店", "保时捷金融服务", "赠送运动套件"},
                     {"迈凯伦 600LT", &McLaren600LT,
                      "迈凯伦 600LT\n\n"
                      "发动机:3.8L V8双涡轮\n"
                      "最大功率:600马力\n"
                      "0-100km/h:2.9秒\n"
                      "变速箱:7速双离合\n"
                      "驱动方式:后轮驱动\n"
                      "价格:¥3,198,000起",
                      "Spider版限量发售", "迈凯伦金融方案", "赠送专业驾驶培训"}};

/**
 * @brief 汽车数据总数
 *
 * 通过计算数组大小自动得出汽车数量，便于循环遍历和数据管理。
 * 当添加或删除汽车数据时，此值会自动更新。
 */
const int car_count = sizeof(cars) / sizeof(cars[0]);

/**
 * @brief 当前显示的汽车索引
 *
 * 用于记录当前在界面上显示的汽车在cars数组中的位置。
 * 初始值为0，表示默认显示第一辆汽车。
 */
int current_car_index = 0;

/**
 * @brief 更新汽车显示
 */
void update_car_display(void)
{
    // 更新汽车图片
    lv_img_set_src(ui.car_img, cars[current_car_index].image);

    // 更新汽车名称
    lv_label_set_text(ui.car_name_label, cars[current_car_index].name);

    // 更新公告信息
    update_announcement_info();
}

/**
 * @brief 更新公告信息
 */
void update_announcement_info(void)
{
    // 设置公告标签文本为当前汽车的公告信息
    lv_label_set_text(ui.announcement_label, cars[current_car_index].announcement);
    // 设置折扣信息标签文本为当前汽车的折扣信息
    lv_label_set_text(ui.discount_label, cars[current_car_index].discount_info);
    // 设置赠品信息标签文本为当前汽车的赠品信息
    lv_label_set_text(ui.gift_label, cars[current_car_index].gift_info);
}