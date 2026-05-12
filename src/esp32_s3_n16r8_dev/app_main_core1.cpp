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
#include "app_file_system.hpp"

static xTaskHandle s_xTaskCore1WiFi;
static xTaskHandle s_xTaskCore1Main;
static bool s_wifi_flg = true;

#if 0
void vTaskCore1WiFi(void *p_parameter)
{
    DBG_PRINTF("[Core1] vTaskCore1WiFi\n");
    app_neopixel_main(16, 0, 0, 0, true, false); // red
    app_wifi_init();

    while (1)
    {
        s_wifi_flg = app_wifi_main();

        if(s_wifi_flg != true){
            DBG_PRINTF("[Core1] vTaskCore1WiFi Suspend now!\n");
            vTaskSuspend(NULL);
            DBG_PRINTF("[Core1] vTaskCore1WiFi Resume!\n");
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
#endif

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
#endif

void app_main_init_core1(void)
{
    xSerialMutex = xSemaphoreCreateMutex();

    // Deep Sleep
    // esp_sleep_enable_timer_wakeup(DEEPSLEEP_TIME_US);

#ifdef SYSTEM_RAM_TEST
    app_fs_system_ram_test();
#endif

#if 0
    xTaskCreatePinnedToCore(vTaskCore1WiFi,     // コールバック関数ポインタ
                            "vTaskCore1WiFi",   // タスク名
                            8192,              // スタック
                            NULL,              // パラメータ
                            3,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1WiFi, // ハンドル
                            CPU_CORE_1);       // Core0 or Core1

    xTaskCreatePinnedToCore(vTaskCore1Main,   // コールバック関数ポインタ
                            "vTaskCore1Main", // タスク名
                            16384,              // スタック
                            NULL,              // パラメータ
                            6,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1Main, // ハンドル
                            CPU_CORE_1);       // Core0 or Core1
#endif
}

void app_main_core1(void)
{
    vTaskSuspend(NULL);
}