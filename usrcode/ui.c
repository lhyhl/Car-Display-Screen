// usrcode/usr_code.c
#include "inc/ui.h"
#include "inc/car_data.h"
#include "inc/time_weather.h"
#include "inc/popup_window.h"

// 全局UI实例定义
display_ui_t ui;

/**
 * @brief 创建用户界面
 * 该函数负责创建整个汽车展示界面的所有UI组件
 */
void create_ui(display_ui_t * ui)
{
    // ==================== 顶部广告区域 ====================
    // 创建广告容器（一个矩形对象）
    lv_obj_t * ad_container = lv_obj_create(ui->screen);
    lv_obj_set_size(ad_container, 250, 25);                   // 设置容器尺寸：宽250像素，高25像素
    lv_obj_align(ad_container, LV_ALIGN_TOP_MID, 0, 8);       // 对齐到屏幕顶部中间，Y轴偏移8像素
    lv_obj_set_style_bg_color(ad_container, ACCENT_COLOR, 0); // 设置背景颜色为强调色
    lv_obj_set_style_radius(ad_container, 5, 0);              // 设置圆角半径为5像素
    lv_obj_set_style_border_width(ad_container, 0, 0);        // 设置边框宽度为0（无边框）
    lv_obj_clear_flag(ad_container, LV_OBJ_FLAG_SCROLLABLE);  // 清除可滚动标志，禁止滚动

    // 在广告容器内创建标签用于显示文字
    ui->ad_label = lv_label_create(ad_container);
    lv_label_set_text(ui->ad_label, "欢迎光临豪华汽车展厅");    // 设置广告文本
    lv_obj_set_style_text_font(ui->ad_label, &chinese_ziku, 0); // 设置中文字体
    lv_obj_set_style_text_color(ui->ad_label, TEXT_COLOR, 0);   // 设置文本颜色
    lv_obj_center(ui->ad_label);                                // 将标签居中显示在容器内

    // ==================== 时间显示 ====================
    // 创建时间显示标签
    ui->time_label = lv_label_create(ui->screen);
    lv_label_set_text(ui->time_label, "加载中...");               // 初始显示文本
    lv_obj_set_style_text_font(ui->time_label, &chinese_ziku, 0); // 设置中文字体
    lv_obj_set_style_text_color(ui->time_label, TEXT_COLOR, 0);   // 设置文本颜色
    lv_obj_set_style_bg_opa(ui->time_label, LV_OPA_0, 0);         // 设置背景透明度为0（完全透明）
    lv_obj_align(ui->time_label, LV_ALIGN_TOP_RIGHT, -15, 10);    // 对齐到右上角

    // ==================== 天气显示 ====================
    // 创建天气显示标签
    ui->weather_label = lv_label_create(ui->screen);
    lv_label_set_text(ui->weather_label, "加载中...");               // 初始显示文本
    lv_obj_set_style_text_font(ui->weather_label, &chinese_ziku, 0); // 设置中文字体
    lv_obj_set_style_text_color(ui->weather_label, TEXT_COLOR, 0);   // 设置文本颜色
    lv_obj_set_style_bg_opa(ui->weather_label, LV_OPA_0, 0);         // 设置背景透明
    lv_obj_align(ui->weather_label, LV_ALIGN_TOP_LEFT, 15, 10);      // 对齐到左上角


    // ==================== 左侧公告区域 ====================

    // 第一个公告文本框 - 用于显示重要通知
    lv_obj_t * announcement_container = lv_obj_create(ui->screen);
    lv_obj_set_size(announcement_container, BOX_WIDTH, BOX_HEIGHT);               // 设置统一尺寸
    lv_obj_align(announcement_container, LV_ALIGN_LEFT_MID, 10, BOX_START_Y);     // 左中对齐，使用统一起始位置
    lv_obj_set_style_bg_color(announcement_container, lv_color_hex(0x1a1a2e), 0); // 深蓝色背景
    lv_obj_set_style_bg_opa(announcement_container, LV_OPA_90, 0);                // 90%不透明度
    lv_obj_set_style_radius(announcement_container, 10, 0);                       // 10像素圆角
    lv_obj_set_style_border_color(announcement_container, ACCENT_COLOR, 0);       // 强调色边框
    lv_obj_set_style_border_width(announcement_container, 2, 0);                  // 2像素边框
    lv_obj_clear_flag(announcement_container, LV_OBJ_FLAG_SCROLLABLE);            // 禁止滚动

    // 公告标签
    ui->announcement_label = lv_label_create(announcement_container);
    lv_label_set_text(ui->announcement_label, "赛道版限量发售,仅剩5台");          // 公告内容
    lv_obj_set_style_text_font(ui->announcement_label, &chinese_ziku, 0);         // 中文字体
    lv_obj_set_style_text_color(ui->announcement_label, TEXT_COLOR, 0);           // 文本颜色
    lv_obj_set_style_text_align(ui->announcement_label, LV_TEXT_ALIGN_CENTER, 0); // 文本居中
    lv_obj_center(ui->announcement_label);                                        // 标签居中

    // 第二个：优惠信息文本框 - 用于显示促销信息
    lv_obj_t * discount_container = lv_obj_create(ui->screen);
    lv_obj_set_size(discount_container, BOX_WIDTH, BOX_HEIGHT);                                      // 设置统一尺寸
    lv_obj_align(discount_container, LV_ALIGN_LEFT_MID, 10, BOX_START_Y + BOX_HEIGHT + BOX_SPACING); // 使用统一间距
    lv_obj_set_style_bg_color(discount_container, lv_color_hex(0x1a1a2e), 0);                        // 深蓝色背景
    lv_obj_set_style_bg_opa(discount_container, LV_OPA_90, 0);                                       // 90%不透明度
    lv_obj_set_style_radius(discount_container, 10, 0);                                              // 10像素圆角
    lv_obj_set_style_border_color(discount_container, lv_color_hex(0x4CAF50), 0);                    // 绿色边框
    lv_obj_set_style_border_width(discount_container, 2, 0);                                         // 2像素边框
    lv_obj_clear_flag(discount_container, LV_OBJ_FLAG_SCROLLABLE);                                   // 禁止滚动

    // 优惠信息标签
    ui->discount_label = lv_label_create(discount_container);
    lv_label_set_text(ui->discount_label, "首付30%,享3年免息");              // 优惠内容（%%表示转义%字符）
    lv_obj_set_style_text_font(ui->discount_label, &chinese_ziku, 0);         // 中文字体
    lv_obj_set_style_text_color(ui->discount_label, TEXT_COLOR, 0);           // 文本颜色
    lv_obj_set_style_text_align(ui->discount_label, LV_TEXT_ALIGN_CENTER, 0); // 文本居中
    lv_obj_center(ui->discount_label);                                        // 标签居中

    // 第三个：礼品信息文本框 - 用于显示赠品信息
    lv_obj_t * gift_container = lv_obj_create(ui->screen);
    lv_obj_set_size(gift_container, BOX_WIDTH, BOX_HEIGHT);                                            // 设置统一尺寸
    lv_obj_align(gift_container, LV_ALIGN_LEFT_MID, 10, BOX_START_Y + 2 * (BOX_HEIGHT + BOX_SPACING)); // 使用统一间距
    lv_obj_set_style_bg_color(gift_container, lv_color_hex(0x1a1a2e), 0);                              // 深蓝色背景
    lv_obj_set_style_bg_opa(gift_container, LV_OPA_90, 0);                                             // 90%不透明度
    lv_obj_set_style_radius(gift_container, 10, 0);                                                    // 10像素圆角
    lv_obj_set_style_border_color(gift_container, lv_color_hex(0xFF9800), 0);                          // 橙色边框
    lv_obj_set_style_border_width(gift_container, 2, 0);                                               // 2像素边框
    lv_obj_clear_flag(gift_container, LV_OBJ_FLAG_SCROLLABLE);                                         // 禁止滚动

    // 礼品信息标签
    ui->gift_label = lv_label_create(gift_container);
    lv_label_set_text(ui->gift_label, "赠送专业赛道驾驶培训");            // 礼品内容
    lv_obj_set_style_text_font(ui->gift_label, &chinese_ziku, 0);         // 中文字体
    lv_obj_set_style_text_color(ui->gift_label, TEXT_COLOR, 0);           // 文本颜色
    lv_obj_set_style_text_align(ui->gift_label, LV_TEXT_ALIGN_CENTER, 0); // 文本居中
    lv_obj_center(ui->gift_label);                                        // 标签居中

    // ==================== 汽车图片展示区域 ====================
    // 创建汽车图片对象
    ui->car_img = lv_img_create(ui->screen);
    // 设置图片源为当前汽车索引对应的图片（cars是汽车数据数组）
    lv_img_set_src(ui->car_img, cars[current_car_index].image);
    lv_obj_set_size(ui->car_img, SCREEN_WIDTH, SCREEN_HEIGHT); // 设置图片大小为屏幕尺寸
    lv_obj_align(ui->car_img, LV_ALIGN_TOP_LEFT, 0, 0);        // 对齐到左上角
    lv_obj_move_background(ui->car_img);                       // 将图片移动到背景层，确保其他UI元素在前景显示

    // ==================== 汽车名称标签 ====================
    // 创建汽车名称显示标签
    ui->car_name_label = lv_label_create(ui->screen);
    lv_obj_set_style_text_font(ui->car_name_label, &chinese_ziku, 0);         // 中文字体
    lv_obj_set_style_text_color(ui->car_name_label, TEXT_COLOR, 0);           // 文本颜色
    lv_obj_set_style_bg_color(ui->car_name_label, lv_color_hex(0x000000), 0); // 黑色背景
    lv_obj_set_style_bg_opa(ui->car_name_label, LV_OPA_50, 0);                // 50%不透明度（半透明）
    lv_obj_set_style_radius(ui->car_name_label, 6, 0);                        // 6像素圆角
    lv_obj_set_style_pad_all(ui->car_name_label, 8, 0);                       // 四周内边距8像素
    lv_obj_set_style_text_align(ui->car_name_label, LV_TEXT_ALIGN_CENTER, 0); // 文本居中
    lv_obj_align(ui->car_name_label, LV_ALIGN_BOTTOM_MID, 0, -50);            // 对齐到底部中间，Y轴偏移-50

    // ==================== 详情按钮 ====================
    // 创建详情按钮
    ui->detail_btn = lv_btn_create(ui->screen);
    lv_obj_set_size(ui->detail_btn, 100, 35);                   // 按钮尺寸：100x35像素
    lv_obj_align(ui->detail_btn, LV_ALIGN_BOTTOM_MID, 0, -8);   // 对齐到底部中间，Y轴偏移-8
    lv_obj_set_style_bg_color(ui->detail_btn, ACCENT_COLOR, 0); // 强调色背景
    lv_obj_set_style_radius(ui->detail_btn, 8, 0);              // 8像素圆角
    // 添加点击事件回调函数
    lv_obj_add_event_cb(ui->detail_btn, detail_btn_callback, LV_EVENT_CLICKED, NULL);

    // 在按钮上创建标签
    lv_obj_t * detail_label = lv_label_create(ui->detail_btn);
    lv_label_set_text(detail_label, "查看详情");                // 按钮文本
    lv_obj_set_style_text_font(detail_label, &chinese_ziku, 0); // 中文字体
    lv_obj_set_style_text_color(detail_label, TEXT_COLOR, 0);   // 文本颜色
    lv_obj_center(detail_label);                                // 标签居中

    // ==================== 左右切换箭头按钮 ====================
    // 左箭头按钮 - 用于切换到上一辆汽车
    ui->prev_btn = lv_btn_create(ui->screen);
    lv_obj_set_size(ui->prev_btn, 60, 60);                     // 按钮尺寸：60x60像素
    lv_obj_align(ui->prev_btn, LV_ALIGN_BOTTOM_LEFT, 20, -20); // 对齐到左下角

    // 设置按钮样式
    lv_obj_set_style_bg_color(ui->prev_btn, lv_color_hex(0x2F2F4F), 0); // 深色背景
    lv_obj_set_style_bg_opa(ui->prev_btn, LV_OPA_80, 0);                // 80%不透明度
    lv_obj_set_style_radius(ui->prev_btn, 30, 0);                       // 圆形按钮
    lv_obj_set_style_border_width(ui->prev_btn, 0, 0);                  // 无边框

    // 按下状态样式
    lv_obj_set_style_bg_color(ui->prev_btn, ACCENT_COLOR, LV_STATE_PRESSED); // 按下时使用强调色
    lv_obj_set_style_bg_opa(ui->prev_btn, LV_OPA_100, LV_STATE_PRESSED);

    // 在按钮上创建左箭头符号
    lv_obj_t * prev_label = lv_label_create(ui->prev_btn);
    lv_label_set_text(prev_label, LV_SYMBOL_LEFT); // 使用LVGL内置左箭头符号
    lv_obj_set_style_text_color(prev_label, TEXT_COLOR, 0);
    lv_obj_set_style_text_font(prev_label, &lv_font_montserrat_24, 0); // 使用合适的字体大小
    lv_obj_center(prev_label);

    // 添加点击事件回调函数
    lv_obj_add_event_cb(ui->prev_btn, prev_car_callback, LV_EVENT_CLICKED, NULL);

    // 右箭头按钮 - 用于切换到下一辆汽车
    ui->next_btn = lv_btn_create(ui->screen);
    lv_obj_set_size(ui->next_btn, 60, 60);                       // 按钮尺寸：60x60像素
    lv_obj_align(ui->next_btn, LV_ALIGN_BOTTOM_RIGHT, -20, -20); // 对齐到右下角

    // 设置按钮样式
    lv_obj_set_style_bg_color(ui->next_btn, lv_color_hex(0x2F2F4F), 0); // 深色背景
    lv_obj_set_style_bg_opa(ui->next_btn, LV_OPA_80, 0);                // 80%不透明度
    lv_obj_set_style_radius(ui->next_btn, 30, 0);                       // 圆形按钮
    lv_obj_set_style_border_width(ui->next_btn, 0, 0);                  // 无边框

    // 按下状态样式
    lv_obj_set_style_bg_color(ui->next_btn, ACCENT_COLOR, LV_STATE_PRESSED); // 按下时使用强调色
    lv_obj_set_style_bg_opa(ui->next_btn, LV_OPA_100, LV_STATE_PRESSED);

    // 在按钮上创建右箭头符号
    lv_obj_t * next_label = lv_label_create(ui->next_btn);
    lv_label_set_text(next_label, LV_SYMBOL_RIGHT); // 使用LVGL内置右箭头符号
    lv_obj_set_style_text_color(next_label, TEXT_COLOR, 0);
    lv_obj_set_style_text_font(next_label, &lv_font_montserrat_24, 0); // 使用合适的字体大小
    lv_obj_center(next_label);

    // 添加点击事件回调函数
    lv_obj_add_event_cb(ui->next_btn, next_car_callback, LV_EVENT_CLICKED, NULL);
    // 初始化显示 - 更新汽车相关信息显示
    update_car_display();
}

/**
 * @brief 详情按钮点击回调函数
 * 当用户点击"查看详情"按钮时调用此函数
 * @param e 事件对象，包含事件相关信息
 */
void detail_btn_callback(lv_event_t * e)
{
    // 显示当前汽车的详细信息弹窗
    show_car_detail_popup(current_car_index);
}

/**
 * @brief 上一辆车回调函数
 * 当用户点击左箭头按钮时调用此函数
 * @param e 事件对象，包含事件相关信息
 */
void prev_car_callback(lv_event_t * e)
{
    // 减少当前汽车索引
    current_car_index--;
    // 如果索引小于0，则循环到最后一张图片
    if(current_car_index < 0) {
        current_car_index = car_count - 1; // car_count是汽车总数
    }
    // 更新汽车显示（图片和名称）
    update_car_display();
}

/**
 * @brief 下一辆车回调函数
 * 当用户点击右箭头按钮时调用此函数
 * @param e 事件对象，包含事件相关信息
 */
void next_car_callback(lv_event_t * e)
{
    // 增加当前汽车索引，使用取模运算实现循环
    current_car_index = (current_car_index + 1) % car_count;
    // 更新汽车显示（图片和名称）
    update_car_display();
}