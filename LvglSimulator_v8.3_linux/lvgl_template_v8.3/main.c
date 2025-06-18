
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/sdl/sdl.h"
#include <stdio.h>
#include "MY_GUI/demo.h"



/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
       void lv_example(void);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
lv_color32_t color_test;

void My_gui();
int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/
  color_test.ch.blue = 100;
  color_test.ch.green = 100;
  color_test.ch.red = 100;
  color_test.ch.alpha = 100;
  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();
  // lv_example();

  //  lv_example_calendar_1();
  //  lv_example_btnmatrix_2();
  //  lv_example_checkbox_1();
  //  lv_example_colorwheel_1();
  //  lv_example_chart_6();
  //  lv_example_table_2();
  //  lv_example_scroll_2();
  //  lv_example_textarea_1();
  //  lv_example_msgbox_1();
  //  lv_example_dropdown_2();
  //  lv_example_btn_1();
  //  lv_example_scroll_1();
  //  lv_example_tabview_1();
  //  lv_example_tabview_1();
  //  lv_example_flex_3();
  //  lv_example_label_1();
create_two_screens();


    float current_speed = 0.0;

// create_bike_cyclometer_ui();

  // lv_demo_widgets();
  // lv_demo_benchmark();

  while (1)
  {
            // 模拟速度变化
        current_speed += 0.05;
        if (current_speed > 60.0) {
            current_speed = 0.0;
        }

        // 更新速度显示
        update_speed_label(current_speed);

    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_timer_handler();
    usleep(2 * 1000);
  }

  return 0;
}



 
// SDL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#if 0 
 
#define POINTS_COUNT 4
 
static SDL_Point points[POINTS_COUNT] = {
	{ 320, 200 },
	{ 300, 240 },
	{ 340, 240 },
	{ 320, 200 }
};
 
static SDL_Rect bigrect = { 0, 0, 280, 280 };
 
int main(int argc, char* argv[])
{
	int flag = 1;
 
	SDL_Window *window;                    // Declare a pointer
	SDL_Renderer *renderer;
 
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
 
	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"SDL2 Draw Window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		800,                               // width, in pixels
		600,                               // height, in pixels
		SDL_WINDOW_SHOWN // flags - see below
		);
 
	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
 
	/* We must call SDL_CreateRenderer in order for draw calls to affect this window. */
	renderer = SDL_CreateRenderer(window, -1, 0);
 
	/* Select the color for drawing. It is set to white here. */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	/* Clear the entire screen to our selected color. */
	SDL_RenderClear(renderer);
 
//  设置颜色，画点
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawPoint(renderer, 500, 500);
 
//  设置颜色，画线
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
 
//  设置颜色，画矩形
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_Rect rect = { 200, 300, 100, 100 };
	SDL_RenderDrawRect(renderer, &rect);
 
//  设置颜色，填充目标矩形区域	
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_Rect rect2 = { 400, 400, 100, 100 };
	SDL_RenderFillRect(renderer, &rect2);
 
//  设置颜色，填充目标矩形区域	
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &bigrect);
 
	/* Up until now everything was drawn behind the scenes.
	This will show the new, red contents of the window. */
	SDL_RenderPresent(renderer);
 
	// The window is open: could enter program loop here (see SDL_PollEvent())
	SDL_Delay(5000);  // Pause execution for 5000 milliseconds, for example
 
	//destory renderer
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
 
	// Close and destroy the window
	SDL_DestroyWindow(window);
 
	// Clean up
	SDL_Quit();
	return 0;
 
}
 
 #endif
/**********************
 *   STATIC FUNCTIONS
 **********************/






static void event_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  // lv_obj_t * obj = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED)
  {
    //  LV_LOG_USER("State: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
    printf("enten\r\n");
  }
}



void lv_example(void)
{
  lv_obj_set_flex_flow(lv_scr_act(), LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(lv_scr_act(), LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  lv_obj_t *sw;

  sw = lv_switch_create(lv_scr_act());
  // lv_obj_add_state(sw, LV_STATE_CHECKED);
  lv_obj_add_event_cb(sw, event_handler, LV_EVENT_CLICKED, NULL);

}

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static void hal_init(void)
{
  /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
  sdl_init();

  /*Create a display buffer*/
  static lv_disp_draw_buf_t disp_buf1;
  static lv_color_t buf1_1[SDL_HOR_RES * 100];
  lv_disp_draw_buf_init(&disp_buf1, buf1_1, NULL, SDL_HOR_RES * 100);

  /*Create a display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.draw_buf = &disp_buf1;
  disp_drv.flush_cb = sdl_display_flush;
  disp_drv.hor_res = SDL_HOR_RES;
  disp_drv.ver_res = SDL_VER_RES;

  lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

  lv_theme_t *th = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
  lv_disp_set_theme(disp, th);

  lv_group_t *g = lv_group_create();
  lv_group_set_default(g);

  /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  static lv_indev_drv_t indev_drv_1;
  lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
  indev_drv_1.type = LV_INDEV_TYPE_POINTER;

  /*This function will be called periodically (by the library) to get the mouse position and state*/
  indev_drv_1.read_cb = sdl_mouse_read;
  lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

  static lv_indev_drv_t indev_drv_2;
  lv_indev_drv_init(&indev_drv_2); /*Basic initialization*/
  indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv_2.read_cb = sdl_keyboard_read;
  lv_indev_t *kb_indev = lv_indev_drv_register(&indev_drv_2);
  lv_indev_set_group(kb_indev, g);

  static lv_indev_drv_t indev_drv_3;
  lv_indev_drv_init(&indev_drv_3); /*Basic initialization*/
  indev_drv_3.type = LV_INDEV_TYPE_ENCODER;
  indev_drv_3.read_cb = sdl_mousewheel_read;
  lv_indev_t *enc_indev = lv_indev_drv_register(&indev_drv_3);
  lv_indev_set_group(enc_indev, g);

  /*Set a cursor for the mouse*/
  LV_IMG_DECLARE(mouse_cursor_icon);                  /*Declare the image file.*/
  lv_obj_t *cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
  lv_img_set_src(cursor_obj, &mouse_cursor_icon);     /*Set the image source*/
  lv_indev_set_cursor(mouse_indev, cursor_obj);       /*Connect the image  object to the driver*/
}
