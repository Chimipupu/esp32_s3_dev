/**
 * @file common.hpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief 共通ヘッダー
 * @version 0.1
 * @date 2025-08-05
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#ifndef COMMON_HPP
#define COMMON_HPP

// C,C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Arduino IDE Lib
#include <Arduino.h>

// FreeRTOS Lib
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

// GPIO
#define RGBLED_PIN        48   // YD-ESP32-S3 RGBLED @GPIO 48
#define BUTTON_PIN        46   // YD-ESP32-S3e Button @GPIO 41

// 割込みマスク・許可
#define __DI            portENTER_CRITICAL
#define __EI            portEXIT_CRITICAL
#define __DI_ISR        portENTER_CRITICAL_ISR
#define __EI_ISR        portEXIT_CRITICAL_ISR

extern portMUX_TYPE g_mux;
extern SemaphoreHandle_t xSerialMutex;

#define DBG_PRINTF      Serial.printf

#define CPU_CORE_0      0
#define CPU_CORE_1      1

#ifndef APP_CORE
// #define APP_CORE        CPU_CORE_0
#define APP_CORE        CPU_CORE_1

#if APPLE_CORE == CPU_CORE_0
#define core0_init    setup
#define core0_main    loop
#else
#define core1_init    setup
#define core1_main    loop
#endif

#define CPU_CORE_0      0
#define CPU_CORE_1      1

// #define APP_CORE        CPU_CORE_0
#define APP_CORE        CPU_CORE_1

#if APP_CORE == CPU_CORE_0
    #define core0_init    setup
    #define core0_main    loop
#else
    #define core1_init    setup
    #define core1_main    loop
#endif
#endif

#ifndef NOP
static inline void NOP(void)
{
    asm volatile("nop");
}
#endif

static inline void WDT_TOGGLE(void)
{
#ifdef __WDT_ENABLE__
    watchdog_update();
#else
    asm volatile("nop");
#endif /* __WDT_ENABLE__ */
}

#endif /* COMMON_HPP */