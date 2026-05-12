/**
 * @file common.hpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief 共通ヘッダー
 * @version 0.1
 * @date 2026-05-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
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

// 自前のヘッダ、ライブラリ
#include "pcb_define.h"

// -----------------------------------------------------------
// [マクロ]

// 8/16/32bitのR/Wマクロ
#define MEM_READ_BYTE(base, offset)           (*(volatile uint8_t  *)((base) + (offset)))         // 8Bit  Read
#define MEM_WRITE_BYTE(base, offset, val)     (*(volatile uint8_t  *)((base) + (offset)) = (val)) // 8Bit Write
#define MEM_READ_WORD(base, offset)           (*(volatile uint16_t *)((base) + (offset)))         // 16Bit  Read
#define MEM_WRITE_WORD(base, offset, val)     (*(volatile uint16_t *)((base) + (offset)) = (val)) // 16Bit Write
#define MEM_READ_DWORD(base, offset)          (*(volatile uint32_t *)((base) + (offset)))         // 32Bit  Read
#define MEM_WRITE_DWORD(base, offset, val)    (*(volatile uint32_t *)((base) + (offset)) = (val)) // 32Bit Write

// ビット操作
#define MEM_BIT_SET(reg, bit)                 ((reg) |=  (1UL << (bit))) // ビット　セット
#define MEM_BIT_CLR(reg, bit)                 ((reg) &= ~(1UL << (bit))) // ビット　クリア
#define MEM_BIT_TGL(reg, bit)                 ((reg) ^=  (1UL << (bit))) // ビット　トグル
#define MEM_BIT_CHK(reg, bit)                 ((reg) &   (1UL << (bit))) // ビット　チェック

// -----------------------------------------------------------
// [Define]

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

// -----------------------------------------------------------
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

// -----------------------------------------------------------

#endif /* COMMON_HPP */