/**
 * @file app_main_core1.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2026-05-13
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 */

#include "common.hpp"
#include "app_main_core0.hpp"
#include "app_memory.h"
#include "app_neopixel.hpp"

// -----------------------------------------------------------
#define TASK_RGBLED_DELAY_MS    (300  / portTICK_PERIOD_MS)
static xTaskHandle vTaskCore0Led_Handle;
// -----------------------------------------------------------
void vTaskCore0Led(void *p_parameter)
{
    // DBG_PRINTF("[Core0] vTaskCore0Led\n");
    app_neopixel_init(RGBLED_NUM, RGBLED_MAX_BRIGHTNESS);

    while (1)
    {
        app_neopixel_rgb_illumination(0);
        vTaskDelay(TASK_RGBLED_DELAY_MS);
    }
}

void app_main_init_core0(void)
{
    // FreeRTOS
    xTaskCreatePinnedToCore(vTaskCore0Led,     // コールバック関数ポインタ
                            "vTaskCore0Led",   // タスク名
                            2048,              // スタック
                            NULL,              // パラメータ
                            0,                 // 優先度(0～7、7が最優先)
                            &vTaskCore0Led_Handle, // ハンドル
                            CPU_CORE_0);       // Core0 or Core1
}

void app_main_core0(void)
{
    // DBG_PRINTF("[Core0] ... loopTask\n");
    // vTaskDelay(10000 / portTICK_PERIOD_MS);
    vTaskSuspend(NULL);
}