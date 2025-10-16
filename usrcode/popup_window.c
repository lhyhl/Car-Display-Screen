// usrcode/popup_window.c
#include "inc/popup_window.h"
#include "inc/ui.h"
#include <stdio.h>

/**
 * @brief 显示汽车详情弹窗
 * 创建一个模态弹窗，显示选定汽车的详细配置信息
 * @param car_index 汽车在数组中的索引，用于获取对应汽车数据
 */
void show_car_detail_popup(int car_index)
{
    // ==================== 弹窗背景容器 ====================
    // 创建弹窗主容器，作为屏幕的直接子对象
    lv_obj_t *popup = lv_obj_create(lv_scr_act());
    // 设置弹窗尺寸：宽650像素，高450像素
    lv_obj_set_size(popup, 650, 450);
    lv_obj_center(popup);  // 将弹窗居中显示在屏幕上
    // 设置弹窗背景颜色为深蓝色（十六进制颜色码0x1a1a2e）
    lv_obj_set_style_bg_color(popup, lv_color_hex(0x1a1a2e), 0);
    lv_obj_set_style_bg_opa(popup, LV_OPA_90, 0);  // 设置背景不透明度为90%（半透明效果）
    lv_obj_set_style_radius(popup, 20, 0);  // 设置圆角半径为20像素
    lv_obj_set_style_border_width(popup, 4, 0);  // 设置边框宽度为4像素
    lv_obj_set_style_border_color(popup, ACCENT_COLOR, 0);  // 设置边框颜色为强调色

    // ==================== 标题区域 ====================
    // 创建标题容器，用于放置标题文本
    lv_obj_t *title_container = lv_obj_create(popup);
    lv_obj_set_size(title_container, 600, 50);  // 标题容器尺寸：600x50像素
    lv_obj_align(title_container, LV_ALIGN_TOP_MID, 0, 10);  // 对齐到弹窗顶部中间，Y轴偏移10像素
    lv_obj_set_style_bg_color(title_container, ACCENT_COLOR, 0);  // 背景色使用强调色
    lv_obj_set_style_radius(title_container, 12, 0);  // 圆角半径12像素
    lv_obj_set_style_border_width(title_container, 0, 0);  // 无边框
    lv_obj_clear_flag(title_container, LV_OBJ_FLAG_SCROLLABLE);  // 禁止滚动

    // 创建标题标签
    lv_obj_t *title = lv_label_create(title_container);
    char title_text[50];  // 缓冲区用于存储格式化后的标题文本
    // 格式化标题文本：汽车图标 + 汽车名称 + "详细配置"
    snprintf(title_text, sizeof(title_text), "%s 详细配置", cars[car_index].name);
    lv_label_set_text(title, title_text);  // 设置标题文本
    lv_obj_set_style_text_font(title, &chinese_ziku, 0);  // 使用中文字体
    lv_obj_set_style_text_color(title, TEXT_COLOR, 0);  // 设置文本颜色
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER, 0);  // 文本居中对齐
    lv_obj_set_style_text_opa(title, LV_OPA_COVER, 0);  // 文本不透明度100%
    lv_obj_set_style_text_letter_space(title, 1, 0);  // 字符间距1像素
    lv_obj_center(title);  // 标题在容器内居中

    // ==================== 详细描述区域 ====================
    // 创建描述内容容器
    lv_obj_t *desc_container = lv_obj_create(popup);
    lv_obj_set_size(desc_container, 620, 320);  // 容器尺寸：620x320像素
    lv_obj_align(desc_container, LV_ALIGN_TOP_MID, 0, 75);  // 对齐到顶部中间，Y轴偏移75像素
    // 设置背景颜色为稍浅的深蓝色
    lv_obj_set_style_bg_color(desc_container, lv_color_hex(0x2a2a3e), 0);
    lv_obj_set_style_bg_opa(desc_container, LV_OPA_80, 0);  // 80%不透明度
    lv_obj_set_style_radius(desc_container, 15, 0);  // 圆角半径15像素
    lv_obj_set_style_border_width(desc_container, 2, 0);  // 2像素边框
    lv_obj_set_style_border_color(desc_container, lv_color_hex(0x4CAF50), 0);  // 绿色边框
    lv_obj_clear_flag(desc_container, LV_OBJ_FLAG_SCROLLABLE);  // 禁止滚动

    // 创建描述文本标签
    lv_obj_t *desc = lv_label_create(desc_container);
    // 直接从汽车数据数组中获取描述文本
    lv_label_set_text(desc, cars[car_index].description);
    lv_obj_set_style_text_font(desc, &chinese_ziku, 0);  // 使用中文字体
    lv_obj_set_style_text_color(desc, TEXT_COLOR, 0);  // 文本颜色
    lv_obj_set_style_text_align(desc, LV_TEXT_ALIGN_LEFT, 0);  // 文本左对齐
    lv_obj_set_style_text_letter_space(desc, 1, 0);  // 字符间距1像素
    lv_obj_set_style_text_line_space(desc, 8, 0);  // 行间距8像素（提高可读性）
    lv_obj_set_width(desc, 580);  // 设置文本宽度为580像素（避免贴边）
    lv_obj_align(desc, LV_ALIGN_TOP_MID, 0, 15);  // 对齐到容器顶部中间，Y轴偏移15像素

    // ==================== 关闭按钮 ====================
    // 创建关闭按钮
    lv_obj_t *close_btn = lv_btn_create(popup);
    lv_obj_set_size(close_btn, 120, 45);  // 按钮尺寸：120x45像素
    lv_obj_align(close_btn, LV_ALIGN_BOTTOM_MID, 0, -20);  // 对齐到底部中间，Y轴偏移-20像素
    lv_obj_set_style_bg_color(close_btn, ACCENT_COLOR, 0);  // 背景色为强调色
    lv_obj_set_style_radius(close_btn, 12, 0);  // 圆角半径12像素
    lv_obj_set_style_border_width(close_btn, 2, 0);  // 2像素边框
    lv_obj_set_style_border_color(close_btn, TEXT_COLOR, 0);  // 边框颜色为文本颜色
    // 设置按钮按下状态的颜色变化（变亮50%）
    lv_obj_set_style_bg_color(close_btn, lv_color_lighten(ACCENT_COLOR, 50), LV_STATE_PRESSED);
    // 添加点击事件回调，传入popup作为用户数据
    lv_obj_add_event_cb(close_btn, close_popup_callback, LV_EVENT_CLICKED, popup);

    // 创建关闭按钮上的文本标签
    lv_obj_t *close_label = lv_label_create(close_btn);
    lv_label_set_text(close_label, "关闭详情");  // 按钮文本
    lv_obj_set_style_text_font(close_label, &chinese_ziku, 0);  // 中文字体
    lv_obj_set_style_text_color(close_label, TEXT_COLOR, 0);  // 文本颜色
    lv_obj_set_style_text_align(close_label, LV_TEXT_ALIGN_CENTER, 0);  // 文本居中
    lv_obj_center(close_label);  // 标签在按钮内居中
}

/**
 * @brief 关闭弹窗回调函数
 * 当用户点击关闭按钮时调用，用于销毁弹窗
 * @param e LVGL事件对象，包含事件相关信息
 */
void close_popup_callback(lv_event_t *e)
{
    // 从事件中获取用户数据（即弹窗对象指针）
    lv_obj_t *popup = (lv_obj_t *)lv_event_get_user_data(e);
    // 删除弹窗对象，释放相关资源
    lv_obj_del(popup);
}