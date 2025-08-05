/**
 * @file app_main_core0.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2025-08-05
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
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
    Serial.printf("[Core1] vTaskCore1WiFi\n");
    app_neopixel_main(16, 0, 0, 0, true, false); // red
    app_wifi_init();

    while (1)
    {
        s_wifi_flg = app_wifi_main();

        if(s_wifi_flg != true){
            Serial.printf("[Core1] vTaskCore1WiFi Suspend now!\n");
            vTaskSuspend(NULL);
            Serial.printf("[Core1] vTaskCore1WiFi Resume!\n");
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
#endif

void vTaskCore1Main(void *p_parameter)
{
    // Serial.printf("[Core1] vTaskCore1Main\n");

    while (1)
    {
#if 0
        if (s_wifi_flg != true)
        {
            // DeepSleep @DEEPSLEEP_TIME_US
            uint32_t dat = (DEEPSLEEP_TIME_US / 60) / 1000000;
            Serial.printf("[Core1] vTaskCore1Main ... No Proc. DeepSleep Now!\n");
            Serial.printf("DeepSleep : %d min\n", dat);
            app_neopixel_main(16, 0, 16, 0, true, false); // 紫
            esp_deep_sleep_start();
        } else {
            // TODO: Core1メインタスクの処理実装
            NOP;
        }
#else
        app_fs_info();
        app_fs_psram_test();
#endif
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main_init_core1(void)
{
    xSerialMutex = xSemaphoreCreateMutex();

    // UART
    Serial.begin(115200);
    while (!Serial) {
        WDT_TOGGLE;
    }

    // PSRAM初期化
    app_fs_psram_init();
    app_fs_psram_test();

    // Deep Sleep
    // esp_sleep_enable_timer_wakeup(DEEPSLEEP_TIME_US);

#if 0
    xTaskCreatePinnedToCore(vTaskCore1WiFi,     // コールバック関数ポインタ
                            "vTaskCore1WiFi",   // タスク名
                            8192,              // スタック
                            NULL,              // パラメータ
                            3,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1WiFi, // ハンドル
                            CPU_CORE_1);       // Core0 or Core1
#endif

    xTaskCreatePinnedToCore(vTaskCore1Main,   // コールバック関数ポインタ
                            "vTaskCore1Main", // タスク名
                            16384,              // スタック
                            NULL,              // パラメータ
                            6,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1Main, // ハンドル
                            CPU_CORE_1);       // Core0 or Core1
}

void app_main_core1(void)
{
    vTaskSuspend(NULL);
}