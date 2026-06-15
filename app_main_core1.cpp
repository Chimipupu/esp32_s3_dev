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
#define TASK_CORE1_MAIN_DELAY_MS      (1000 / portTICK_PERIOD_MS)

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
#ifdef USE_DEEP_SLEEP
        if (is_wifi_task_all_proc_end == true) {
            DBG_PRINTF("Now on DeepSleep\n");
            app_neopixel_set_rgb(0, &rgb); // LED消灯

            // DeepSleep開始
            esp_deep_sleep_start();
        }
#endif
        DBG_PRINTF("SoC Temperature: %.2f °C\r\n", temperatureRead());
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

#ifdef USE_DEEP_SLEEP
    // Deep Sleepからの起床確認
    if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
        DBG_PRINTF("[Core1] Wakeup from DeepSleep!\n");
    }

    // Deep Sleep 有効化
    esp_sleep_enable_timer_wakeup(DEEPSLEEP_TIME_US);
#endif

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