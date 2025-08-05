/**
 * @file esp32_s3_n16r8_dev.ino
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief Arduino IDE用ファイル
 * @version 0.1
 * @date 2025-08-05
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#include "common.hpp"
#include "app_main_core0.hpp"
#include "app_main_core1.hpp"
#include "app_file_system.hpp"

SemaphoreHandle_t xSerialMutex;
portMUX_TYPE g_mux = portMUX_INITIALIZER_UNLOCKED;

#if 0
// CPU Core0
void vTaskCore0Main(void *p_parameter)
{
    // app_main_init_core0();

    while (1)
    {
#if 1
        app_fs_info();
        app_fs_psram_test();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
#else
        app_main_core0();
        vTaskDelay(100 / portTICK_PERIOD_MS);
#endif
    }
}
#endif

#if 1
// CPU Core1
void core1_init(void)
{
    Serial.begin(115200);
    // app_main_init_core1();
    app_fs_psram_init();

#if 0
    xTaskCreatePinnedToCore(vTaskCore0Main,    // コールバック関数ポインタ
                            "vTaskCore0Main",  // タスク名
                            8192,              // スタック
                            NULL,              // パラメータ
                            2,                 // 優先度(0～7、7が最優先)
                            NULL,              // ハンドル
                            CPU_CORE_0);       // Core0 or Core1
#endif
}

void core1_main(void)
{
#if 1
    DBG_PRINTF("\n[DEBUG] ESP32-S3 N16R8 Develop\n");
    app_fs_info();
    app_fs_psram_test();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
#else
    app_main_core1();
#endif
}
#endif