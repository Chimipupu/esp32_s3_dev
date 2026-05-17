/**
 * @file app_main_core0.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2026-05-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#include "common.hpp"
#include "app_main_core1.hpp"
#include "app_memory.h"
#include "app_ui.h"

// -----------------------------------------------------------
#if 0
static xTaskHandle s_xTaskCore1Main;
static xTaskHandle s_xTaskCore1Ui;
#endif
// -----------------------------------------------------------

#if 0
void vTaskCore1Main(void *p_parameter)
{
    // DBG_PRINTF("[Core1] vTaskCore1Main\n");

    while (1)
    {
        if (s_wifi_flg != true)
        {
            // DeepSleep @DEEPSLEEP_TIME_US
            uint32_t dat = (DEEPSLEEP_TIME_US / 60) / 1000000;
            DBG_PRINTF("[Core1] vTaskCore1Main ... No Proc. DeepSleep Now!\n");
            DBG_PRINTF("DeepSleep : %d min\n", dat);
            app_neopixel_main(16, 0, 16, 0, true, false); // 紫
            esp_deep_sleep_start();
        } else {
            // TODO: Core1メインタスクの処理実装
            NOP;
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void vTaskCore1Ui(void *p_parameter)
{
    app_ui_init();

    while (1)
    {
        app_ui_main();
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}
#endif

void app_main_init_core1(void)
{
    xSerialMutex = xSemaphoreCreateMutex();

    // Deep Sleep
    // esp_sleep_enable_timer_wakeup(DEEPSLEEP_TIME_US);

#ifdef DEBUG_RAM_TEST
    app_mem_test();
#endif

#if 0
    xTaskCreatePinnedToCore(vTaskCore1Main,   // コールバック関数ポインタ
                            "vTaskCore1Main", // タスク名
                            2048,              // スタック
                            NULL,              // パラメータ
                            3,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1Main, // ハンドル
                            CPU_CORE_1);       // Core0 or Core1

    xTaskCreatePinnedToCore(vTaskCore1Ui,      // コールバック関数ポインタ
                            "vTaskCore1Ui",    // タスク名
                            4096,              // スタック
                            NULL,              // パラメータ
                            1,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1Ui,   // ハンドル
                            CPU_CORE_1);       // Core0 or Core1
#endif
}

void app_main_core1(void)
{
    vTaskSuspend(NULL);
}