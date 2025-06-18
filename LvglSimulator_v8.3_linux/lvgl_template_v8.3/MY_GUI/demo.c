#include "demo.h"
#include "lvgl/lvgl.h"
#include "stdio.h"

void create_bike_cyclometer_ui(lv_obj_t *src_get);

void My_gui()
{
}

int fun1(void)
{

    return 0;
}

static lv_obj_t *screen1;
static lv_obj_t *screen2;

static void btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *current_screen = lv_scr_act();

    if (code == LV_EVENT_GESTURE)
    {
        // 获取当前屏幕
        // 假设我们有两个屏幕 screen1 和 screen2
        if ((current_screen == screen1)&(lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT))
        {
            lv_scr_load_anim(screen2, LV_SCR_LOAD_ANIM_OVER_LEFT, 300, 100, false);
        }
        else if ((current_screen == screen2)&(lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP))
        {
            lv_scr_load_anim(screen1, LV_SCR_LOAD_ANIM_FADE_ON, 300, 100, false);
        }
    }
    if (code == LV_EVENT_CLICKED)
    {
        if (current_screen == screen1)
        {
            // 从 screen1 切换到 screen2，使用淡入动画，速度 300，延迟 100 毫秒，不删除旧屏幕
            lv_scr_load_anim(screen2, LV_SCR_LOAD_ANIM_OVER_TOP, 300, 100, false);
            printf("change\r\n");
        }
        else if (current_screen == screen2)
        {
            // 从 screen2 切换到 screen1，使用淡入动画，速度 300，延迟 100 毫秒，不删除旧屏幕
            lv_scr_load_anim(screen1, LV_SCR_LOAD_ANIM_FADE_ON, 300, 100, false);
        }
    }
}

// 创建两个屏幕及切换按钮的函数
void create_two_screens()
{
    // 创建两个屏幕
    screen1 = lv_obj_create(NULL);
    screen2 = lv_obj_create(NULL);

    // 在 screen1 上创建一个按钮
    lv_obj_t *btn_on_screen1 = lv_btn_create(screen1);
    lv_obj_set_pos(btn_on_screen1, 100, 400);
    lv_obj_set_size(btn_on_screen1, 120, 50);

    // 为 screen1 上的按钮添加标签
    lv_obj_t *label_on_screen1 = lv_label_create(btn_on_screen1);
    lv_label_set_text(label_on_screen1, "Go to Screen 2");
    lv_obj_center(label_on_screen1);

    // 为 screen1 上的按钮添加事件处理函数
    lv_obj_add_event_cb(screen1, btn_event_cb, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(btn_on_screen1, btn_event_cb, LV_EVENT_ALL, NULL);

    create_bike_cyclometer_ui(screen1);

    // 在 screen2 上创建一个按钮
    lv_obj_t *btn_on_screen2 = lv_btn_create(screen2);
    lv_obj_set_pos(btn_on_screen2, 100, 400);
    lv_obj_set_size(btn_on_screen2, 120, 50);

    // 为 screen2 上的按钮添加标签
    lv_obj_t *label_on_screen2 = lv_label_create(btn_on_screen2);
    lv_label_set_text(label_on_screen2, "Go to Screen 1");
    lv_obj_center(label_on_screen2);

    // 为 screen2 上的按钮添加事件处理函数
    lv_obj_add_event_cb(screen2, btn_event_cb, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(btn_on_screen2, btn_event_cb, LV_EVENT_ALL, NULL);

    // 初始加载 screen1 屏幕
    lv_scr_load(screen1);
    // lv_scr_load(screen2);
}

// 用于显示速度的标签
static lv_obj_t *speed_label;
// 用于显示标题的标签
static lv_obj_t *title_label;
// 用于显示速度单位的标签
static lv_obj_t *unit_label;
// 速度显示区域的容器
static lv_obj_t *speed_container;
// 动态图标
static lv_obj_t *icon_obj;
// 表盘对象
static lv_obj_t *dial_obj;

// 更新速度显示
void update_speed_label(float speed)
{
    char speed_str[20];
    // 将速度值格式化为字符串，保留一位小数
    snprintf(speed_str, sizeof(speed_str), "%.1f", speed);
    // 更新标签显示的文本
    lv_label_set_text(speed_label, speed_str);

    lv_color_t new_color;
    if (speed <= 15)
    {
        // 速度低于等于 25 时为白色
        new_color = lv_color_hex(0xFFFFFF);
    }
    else
    {
        // 计算颜色过渡，速度越快越红
        float ratio = (speed - 15) / 25; // 计算速度在 25 - 60 区间的比例
        if (ratio > 1)
        {
            ratio = 1;
        }
        uint8_t red = 255;
        uint8_t green = (uint8_t)((1 - ratio) * 255);
        uint8_t blue = (uint8_t)((1 - ratio) * 255);
        new_color = lv_color_make(red, green, blue);

    }
    lv_obj_set_style_text_color(speed_label, new_color, LV_PART_MAIN);
    lv_obj_set_style_arc_color(dial_obj, new_color, LV_PART_INDICATOR);

    // 根据速度旋转表盘指针
    int angle = (int)((speed / 60) * 270 - 135); // 速度 0 - 60 对应角度 -135 到 135 度
    lv_img_set_angle(icon_obj, angle);
}

// 创建自行车码表界面
void create_bike_cyclometer_ui(lv_obj_t *src_get)
{
    // 获取当前活动屏幕
    lv_obj_t *scr = src_get;

    // 设置深色背景
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x111111), LV_PART_MAIN);

    // 创建标题标签
    title_label = lv_label_create(scr);
    lv_label_set_text(title_label, "Bike Cyclometer");
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFA500), LV_PART_MAIN);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 20);

    // 创建表盘
    dial_obj = lv_arc_create(scr);
    lv_obj_set_size(dial_obj, 250, 250);
    lv_obj_center(dial_obj);
    lv_arc_set_angles(dial_obj, 0, 360);               // 显示 360 度的圆弧
    lv_obj_remove_style(dial_obj, NULL, LV_PART_KNOB); /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(dial_obj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_width(dial_obj, 10, LV_PART_MAIN);
    lv_obj_set_style_arc_color(dial_obj, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_arc_opa(dial_obj, LV_OPA_50, LV_PART_MAIN);

    // 创建速度显示区域的容器
    speed_container = lv_obj_create(scr);
    lv_obj_set_size(speed_container, 150, 150);
    lv_obj_center(speed_container);
    // lv_obj_set_style_bg_color(speed_container, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_radius(speed_container, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_border_width(speed_container, 0, LV_PART_MAIN);

    // 创建速度标签
    speed_label = lv_label_create(speed_container);
    lv_obj_set_style_text_color(speed_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(speed_label, &lv_font_montserrat_48, LV_PART_MAIN);
    lv_obj_center(speed_label);

    // 创建速度单位标签
    unit_label = lv_label_create(speed_container);
    lv_label_set_text(unit_label, "km/h");
    lv_obj_set_style_text_color(unit_label, lv_color_hex(0xFFA500), LV_PART_MAIN);
    lv_obj_set_style_text_font(unit_label, &lv_font_montserrat_18, LV_PART_MAIN);
    lv_obj_align(unit_label, LV_ALIGN_BOTTOM_MID, 0, -10);

    // // 创建动态指针图标
    icon_obj = lv_img_create(scr);
    static lv_img_dsc_t needle_icon = {
        .header.always_zero = 0,
        .header.w = 10,
        .header.h = 120,
        .data_size = 10 * 120 * 2,
        .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
        .data = (const uint8_t *)"这里需要替换为实际的指针图标数据"};
    // lv_img_set_src(icon_obj, &needle_icon);
    // lv_obj_center(icon_obj);
    // lv_img_set_angle(icon_obj, -135); // 初始角度
}
// 动态图标旋转动画
void animate_icon()
{
    // static int angle = 0;
    // angle = (angle + 1) % 360;
    // lv_img_set_angle(icon_obj, angle);
}