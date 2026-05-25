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
#include "app_wifi.h"
#include "app_neopixel.hpp"

// -----------------------------------------------------------
#define TASK_CORE1_MAIN_DELAY_MS      (100 / portTICK_PERIOD_MS)


#if 0
static TaskHandle_t s_xTaskCore1Ui;
#endif
static TaskHandle_t s_xTaskCore1Main;
static TaskHandle_t s_xTaskCore1WiFi_Handle;
// -----------------------------------------------------------

void vTaskCore1Main(void *p_parameter)
{
    led_color_t rgb = {0, 0, 0};

    // DBG_PRINTF("[Core1] vTaskCore1Main\n");

    while (1)
    {
        // WiFiタスクが全仕事が終わってSuspendだったらDeepSleep
        if (is_wifi_task_all_proc_end == true) {
            uint32_t dat = (DEEPSLEEP_TIME_US / 60) / 1000000;
            DBG_PRINTF("[Core1] All Task Proc End\n");
            DBG_PRINTF("Now on DeepSleep\n");
            DBG_PRINTF("WakeUp: %d min after! Goodnight zzz\n", dat);
            app_neopixel_set_rgb(0, &rgb); // LED消灯

            // DeepSleep開始
            esp_deep_sleep_start();
        }
        vTaskDelay(TASK_CORE1_MAIN_DELAY_MS);
    }
}

#if 0
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
    // xSerialMutex = xSemaphoreCreateMutex();

    // Deep Sleep
    // esp_sleep_enable_timer_wakeup(DEEPSLEEP_TIME_US);

#ifdef DEBUG_RAM_TEST
    app_mem_test();
#endif

    xTaskCreatePinnedToCore(vTaskCore1Main,    // コールバック関数ポインタ
                            "vTaskCore1Main",  // タスク名
                            4096,              // スタック
                            NULL,              // パラメータ
                            5,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1Main, // ハンドル
                            CPU_CORE_1);       // Core0 or Core1

#if 0
    xTaskCreatePinnedToCore(vTaskCore1Ui,      // コールバック関数ポインタ
                            "vTaskCore1Ui",    // タスク名
                            4096,              // スタック
                            NULL,              // パラメータ
                            1,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1Ui,   // ハンドル
                            CPU_CORE_1);       // Core0 or Core1
#endif

    xTaskCreatePinnedToCore(vTaskCore1WiFi,    // コールバック関数ポインタ
                            "vTaskCore1WiFi",  // タスク名
                            8192,              // スタック
                            NULL,              // パラメータ
                            3,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1WiFi_Handle, // ハンドル
                            CPU_CORE_1);       // Core0 or Core1
}

void app_main_core1(void)
{
    vTaskSuspend(NULL);
}