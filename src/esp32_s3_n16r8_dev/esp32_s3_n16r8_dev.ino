/**
 * @file esp32_s3_n16r8_dev.ino
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief Arduino IDE用ファイル
 * @version 0.1
 * @date 2026-05-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#include "common.hpp"
#include "app_main_core0.hpp"
#include "app_main_core1.hpp"
#include "app_memory.h"

SemaphoreHandle_t xSerialMutex;
portMUX_TYPE g_mux = portMUX_INITIALIZER_UNLOCKED;

// -----------------------------------------------------------
// [CPU Core 0関連]
#if 0
// CPU Core0
void vTaskCore0Main(void *p_parameter)
{
    // app_main_init_core0();

    while (1)
    {
        app_main_core0();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
#endif

// -----------------------------------------------------------
// [CPU Core 1関連]
void core1_init(void)
{
    // UART初期化
    Serial.begin(UART_BAUD);
    // while (!Serial) {
    //     WDT_TOGGLE;
    // }
    DBG_PRINTF("\n[DEBUG] ESP32-S3 N16R8 Develop\n");

    // PSRAM初期化
    app_mem_psram_init();
    app_mem_info();

    // CPU Core 0 関連初期化
    app_main_init_core0();

#if 0
    xTaskCreatePinnedToCore(vTaskCore0Main,    // コールバック関数ポインタ
                            "vTaskCore0Main",  // タスク名
                            8192,              // スタック
                            NULL,              // パラメータ
                            2,                 // 優先度(0～7、7が最優先)
                            NULL,              // ハンドル
                            CPU_CORE_0);       // Core0 or Core1
#endif

    // CPU Core 1 関連初期化
    app_main_init_core1();
}

void core1_main(void)
{
    app_main_core1();
}