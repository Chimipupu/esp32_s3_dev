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

#include "FS.h"
#include "FFat.h"

// -----------------------------------------------------------
// [コンパイルスイッチ]
#define DEBUG_RAM_TEST // RAMテスト(SRAM, PSRAM)

// -----------------------------------------------------------
// [Define]

#define HEAP_SRAM                 0x00
#define HEAP_PSRAM                0x01
#define HEAP_PSRAM_8BIT           0x10
#define HEAP_PSRAM_32BIT          0x20

#define PSRAM_MALLOC_TEST_SIZE    8

#define FILE_SYSTEM               FFat

// -----------------------------------------------------------
void app_fs_info(void);
void* app_fs_heap_malloc(size_t size, uint8_t type);
void app_fs_psram_init(void);

#ifdef DEBUG_RAM_TEST
void app_fs_system_ram_test(void);
#endif

// -----------------------------------------------------------

#endif /* APP_MEMORY_H */