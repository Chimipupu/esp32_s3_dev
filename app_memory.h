/**
 * @file app_memory.h
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief アプリ用メモリ
 * @version 0.1
 * @date 2026-05-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#ifndef APP_MEMORY_H
#define APP_MEMORY_H

#include "common.hpp"

#if 0
#include "FS.h"
#include "FFat.h"
#define FILE_SYSTEM               FFat
#endif

// -----------------------------------------------------------
// [コンパイルスイッチ]

// -----------------------------------------------------------
// [Define]

#define HEAP_SRAM                 0x00
#define HEAP_PSRAM                0x01
#define HEAP_PSRAM_8BIT           0x10
#define HEAP_PSRAM_32BIT          0x20

#define PSRAM_MALLOC_TEST_SIZE    8

// -----------------------------------------------------------
void app_mem_info(void);
void* app_mem_heap_malloc(size_t size, uint8_t type);
void app_mem_psram_init(void);

// -----------------------------------------------------------

#endif /* APP_MEMORY_H */