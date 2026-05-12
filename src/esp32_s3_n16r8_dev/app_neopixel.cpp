/**
 * @file app_neopixel.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief NeoPixelアプリ
 * @version 0.1
 * @date 2026-05-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */
#include "app_neopixel.hpp"

#define COLOR_TBL_CNT    0x0A

// LEDカラーテーブル

const led_color_data_t g_led_color_tbl[] = {
//     | R | G | B |
    { {255,   0,   0}, "RED" },     // 赤
    { {  0, 255,   0}, "GREEN" },   // 緑
    { {  0,   0, 255}, "BLUE" },    // 青
    { {255, 255, 255}, "WHITE" },   // 白
    { {255, 255,   0}, "YELLOW" },  // 黄
    { {255,   0, 255}, "MAGENTA" }, // マゼンタ
    { {  0, 255, 255}, "CYAN" },    // シアン
    { {255, 165,   0}, "ORANGE" },  // オレンジ
    { {128,   0, 128}, "PURPLE" },  // パープル
    { {  0,   0,   0}, "OFF" }      // オフ（黒）
};
const uint8_t LED_COLOR_TBL_SIZE = sizeof(g_led_color_tbl) / sizeof(g_led_color_tbl[0]);

Adafruit_NeoPixel g_pixel(RGBLED_NUM, RGBLED_PIN, NEO_GRB + NEO_KHZ800);

/**
 * @brief RGB LED 初期化
 */
void app_neopixel_init(void)
{
    g_pixel.begin();
    g_pixel.clear();
    g_pixel.show();
}

/**
 * @brief 指定のNeopixelの色を設定
 * @param led_no Neopixelの指定
 * @param p_rgb RGB色構造体ポインタ
 */
void app_neopixel_set_rgb(uint8_t led_no, led_color_t *p_rgb)
{
    g_pixel.clear();
    g_pixel.setPixelColor(led_no, g_pixel.Color(p_rgb->red, p_rgb->green, p_rgb->blue));
    g_pixel.show();
}

/**
 * @brief 指定のNeopixelの色を設定
 * @param led_no Neopixelの指定
 * @param color 色の名前
 */
void app_neopixel_set_color(uint8_t led_no, uint8_t color)
{
    g_pixel.clear();
    if(color < NEOPIXCEL_COLOR_OFF)
    {
        g_pixel.setPixelColor(led_no, g_pixel.Color(
            LED_SCALE8(g_led_color_tbl[color].rgb.red),
            LED_SCALE8(g_led_color_tbl[color].rgb.green),
            LED_SCALE8(g_led_color_tbl[color].rgb.blue)
            ));
    } else {
        g_pixel.setPixelColor(led_no, g_pixel.Color(
            LED_SCALE8(g_led_color_tbl[NEOPIXCEL_COLOR_OFF].rgb.red),
            LED_SCALE8(g_led_color_tbl[NEOPIXCEL_COLOR_OFF].rgb.green),
            LED_SCALE8(g_led_color_tbl[NEOPIXCEL_COLOR_OFF].rgb.blue)
            ));
    }
    g_pixel.show();
}