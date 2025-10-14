// usrcode/car_data.c
#include "car_data.h"
#include "usr_code.h"



// 汽车数据数组
car_info_t cars[] = {
    {
        "福特 GT500",
        &GT500,
        "福特 GT500\n\n"
        "发动机:5.2L V8机械增压\n"
        "最大功率:760马力\n"
        "0-100km/h:3.3秒\n"
        "变速箱:7速双离合\n"
        "驱动方式:后轮驱动\n"
        "价格:¥1,280,000起",
        "赛道版限量发售,仅剩5台",
        "首付30%%,享3年免息",
        "赠送专业赛道驾驶培训"
    },
    {
        "梅赛德斯-奔驰", 
        &Mercedes,
        "梅赛德斯-奔驰 S级\n\n"
        "发动机:3.0T L6+48V轻混\n"
        "最大功率:435马力\n"
        "变速箱:9速自动\n"
        "驱动方式:后轮/四轮驱动\n"
        "轴距:3216mm\n"
        "价格:¥898,000起",
        "全新一代S级震撼上市",
        "置换补贴最高8万元", 
        "赠送5年免费保养"
    },
    {
        "劳斯莱斯 飓风",
        &RollsRoyceHurricane,
        "劳斯莱斯 飓风\n\n"
        "发动机:6.75L V12双涡轮\n"
        "最大功率:600马力\n"
        "变速箱:8速自动\n"
        "驱动方式:全时四驱\n"
        "车身长度:5990mm\n"
        "价格:¥7,800,000起",
        "定制版现车到店",
        "专属金融方案,首付50%%", 
        "赠送终身保养"
    }
};

const int car_count = sizeof(cars) / sizeof(cars[0]);
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
    lv_label_set_text(ui.announcement_label, cars[current_car_index].announcement);
    lv_label_set_text(ui.discount_label, cars[current_car_index].discount_info);
    lv_label_set_text(ui.gift_label, cars[current_car_index].gift_info);
}