/**
 * @file app_main_core1.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2026-05-13
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#include "common.hpp"
#include "app_main_core0.hpp"
#include "app_neopixel.hpp"

// -----------------------------------------------------------
#define TASK_RGBLED_DELAY_MS    (1000 / portTICK_PERIOD_MS)

static led_color_t s_rgb;
// -----------------------------------------------------------

void core0RgbLedTask(void *p_parameter)
{
    static uint8_t s_color = 0;

    // DBG_PRINTF("[Core0] ... core0RgbLedTask\n");
    app_neopixel_init();
    app_neopixel_set_color(0, NEOPIXCEL_COLOR_OFF);

    while (1)
    {
        s_rgb = g_led_color_tbl[s_color].rgb;
        app_neopixel_set_rgb(0, &s_rgb);
#if 1
        if(g_led_color_tbl[s_color].p_color_str != NULL) {
            DBG_PRINTF("[Core0] RGBLED Color: %s\r\n", g_led_color_tbl[s_color].p_color_str);
        }
#endif
        s_color = (s_color + 1) % LED_COLOR_TBL_SIZE;

        vTaskDelay(TASK_RGBLED_DELAY_MS);
    }
}

void app_main_init_core0(void)
{
    // FreeRTOS
    xTaskCreatePinnedToCore(core0RgbLedTask,   // コールバック関数ポインタ
                            "core0RgbLedTask", // タスク名
                            2048,              // スタック
                            NULL,              // パラメータ
                            0,                 // 優先度(0～7、7が最優先)
                            NULL,              // ハンドル
                            CPU_CORE_0);       // Core0 or Core1
}

void app_main_core0(void)
{
    // DBG_PRINTF("[Core0] ... loopTask\n");
    // vTaskDelay(10000 / portTICK_PERIOD_MS);
    vTaskSuspend(NULL);
}