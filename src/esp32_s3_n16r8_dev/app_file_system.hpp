/**
 * @file app_file_system.hpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief ファイルシステムのアプリヘッダー
 * @version 0.1
 * @date 2025-08-05
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#ifndef APP_FILE_SYSTEM_HPP
#define APP_FILE_SYSTEM_HPP

#include "common.hpp"

// コンパイラスイッチ: RAMテスト(SRAMとPSRAM)
#define SYSTEM_RAM_TEST

#define HEAP_SRAM                 0x00
#define HEAP_PSRAM                0x01
#define HEAP_PSRAM_8BIT           0x10
#define HEAP_PSRAM_32BIT          0x20

#define PSRAM_MALLOC_TEST_SIZE    8

#include "FS.h"
#include "FFat.h"
#define FILE_SYSTEM     FFat
void app_fs_info(void);
void* app_fs_heap_malloc(size_t size, uint8_t type);
void app_fs_psram_init(void);

#ifdef SYSTEM_RAM_TEST
void app_fs_system_ram_test(void);
#endif

#endif /* APP_FILE_SYSTEM_HPP */