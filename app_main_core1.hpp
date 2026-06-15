/**
 * @file app_main_core1.hpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2026-05-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#ifndef APP_MAIN_CORE1_HPP
#define APP_MAIN_CORE1_HPP

// FreeRTOS
#include <task.h>

// -----------------------------------------------------------
// [コンパイルスイッチ]
#define USE_DEEP_SLEEP

// -----------------------------------------------------------
void app_main_init_core1(void);
void app_main_core1(void);

// -----------------------------------------------------------

#endif /* APP_MAIN_CORE1_HPP */