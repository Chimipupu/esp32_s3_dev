/**
 * @file app_memory.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief アプリ用メモリ
 * @version 0.1
 * @date 2026-05-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#include "app_memory.h"

// -----------------------------------------------------------
// NOTE: キャッシュサイズは32KB
#define BUF_MAX_SIZE    (32 *1024)
// #define BUF_MAX_SIZE    (64 *1024)
// #define BUF_MAX_SIZE    (128 *1024)

static bool s_is_psram = false;
static uint32_t s_heap_size = 0;
static uint32_t s_free_size = 0;
static void _heap_print(uint8_t type);

// -----------------------------------------------------------
// [Static]

static void _heap_print(uint8_t type)
{
    switch (type)
    {
        case HEAP_SRAM:
            s_heap_size = ESP.getHeapSize();
            s_free_size = ESP.getFreeHeap();
            DBG_PRINTF("SRAM Heap Size: %lu Byte\n", s_heap_size);
            DBG_PRINTF("SRAM Heap Free: %lu Byte\n", s_free_size);
            break;

        case HEAP_PSRAM:
            s_heap_size = ESP.getPsramSize();
            s_free_size = ESP.getFreePsram();
            DBG_PRINTF("PSRAM Heap Size: %lu Byte\n", s_heap_size);
            DBG_PRINTF("PSRAM Heap Free: %lu Byte\n", s_free_size);
            break;

        default:
            break;
    }
}

// -----------------------------------------------------------
// [API]

/**
 * @brief メモリ情報表示
 */
void app_mem_info(void)
{
    _heap_print(HEAP_SRAM);

    if (s_is_psram == true) {
        _heap_print(HEAP_PSRAM);
    }
}

/**
 * @brief malloc(SRAM or PSRAM)のラッパー
 * @param size mallocするサイズ
 * @param type SRAM or PSRAM
 * @return void* mallocした領域
 */
void* app_mem_heap_malloc(size_t size, uint8_t type)
{
    void *p_malloc = NULL;

    switch (type)
    {
        case HEAP_SRAM:
            p_malloc = heap_caps_malloc(size, MALLOC_CAP_32BIT);
            break;

        case HEAP_PSRAM_8BIT:
            p_malloc = heap_caps_malloc(size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
            break;

        case HEAP_PSRAM_32BIT:
            p_malloc = heap_caps_malloc(size, MALLOC_CAP_SPIRAM | MALLOC_CAP_32BIT);
            break;

        default:
            break;
    }

    return p_malloc;
}

/**
 * @brief PSRAMの初期化
 */
void app_mem_psram_init(void)
{
    s_is_psram = psramInit();
    if (s_is_psram) {
        DBG_PRINTF("PSRAM Inited\n");
    } else {
        DBG_PRINTF("This ESP32 is PSRAM does not exist\n");
    }
}