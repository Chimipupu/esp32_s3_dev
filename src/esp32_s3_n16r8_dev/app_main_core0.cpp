/**
 * @file app_main_core1.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2026-01-26
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#include "common.hpp"
#include "app_main_core0.hpp"
#include "app_neopixel.hpp"

void core0RgbLedTask(void *p_parameter)
{
    static uint8_t s_color = 0;

    // DBG_PRINTF("[Core0] ... core0RgbLedTask\n");
    app_neopixel_init();
    app_neopixel_set_color(0, NEOPIXCEL_COLOR_OFF);

    while (1)
    {
        app_neopixel_set_color(0, s_color);
        s_color = (s_color + 1) % NEOPIXCEL_COLOR_OFF;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
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