/**
 * @file app_file_system.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief ファイルシステムのアプリ
 * @version 0.1
 * @date 2025-08-05
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#include "app_file_system.hpp"

static bool s_is_psram = false;
static uint32_t s_heap_size = 0;
static uint32_t s_free_size = 0;
static void heap_print(uint8_t type);

static void heap_print(uint8_t type)
{
    switch (type)
    {
        case HEAP_SRAM:
            s_heap_size = ESP.getHeapSize();
            s_free_size = ESP.getFreeHeap();
            DBG_PRINTF("SRAM Heap Size: %d Byte\n", s_heap_size);
            DBG_PRINTF("SRAM Heap Free: %d Byte\n", s_free_size);
            break;

        case HEAP_PSRAM:
            s_heap_size = ESP.getPsramSize();
            s_free_size = ESP.getFreePsram();
            DBG_PRINTF("PSRAM Heap Size: %d Byte\n", s_heap_size);
            DBG_PRINTF("PSRAM Heap Free: %d Byte\n", s_free_size);
            break;

        default:
            break;
    }
}

/**
 * @brief ファイルシステム関連の情報表示
 * 
 */
void app_fs_info(void)
{
    heap_print(HEAP_SRAM);
    heap_print(HEAP_PSRAM);
}

/**
 * @brief malloc(SRAM or PSRAM)のラッパー
 * 
 * @param size mallocするサイズ
 * @param type SRAM or PSRAM
 * @return void* mallocした領域
 */
void* app_fs_heap_malloc(size_t size, uint8_t type)
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
 * 
 */
void app_fs_psram_init(void)
{
    s_is_psram = psramInit();
    if (s_is_psram) {
        DBG_PRINTF("PSRAM Inited\n");
    } else {
        DBG_PRINTF("This ESP32 is PSRAM does not exist\n");
    }
}

/**
 * @brief PSRAMのテスト
 * 
 */
void app_fs_psram_test(void)
{
    uint8_t *p_psram_ptr = NULL;
    s_is_psram = psramFound();

    if (s_is_psram) {
        heap_print(HEAP_PSRAM);
        DBG_PRINTF("[PSRAM Test]\n");
        DBG_PRINTF("PSRAM malloc size = %d byte\n", PSRAM_MALLOC_TEST_SIZE);
        p_psram_ptr = (uint8_t *)app_fs_heap_malloc(PSRAM_MALLOC_TEST_SIZE, HEAP_PSRAM_8BIT);
        if (p_psram_ptr != NULL) {
            p_psram_ptr[0] = 0x12;
            p_psram_ptr[1] = 0x34;
            p_psram_ptr[2] = 0x56;
            p_psram_ptr[3] = 0xAB;
            p_psram_ptr[4] = 0xCD;
            p_psram_ptr[5] = 0xEF;
            DBG_PRINTF("[DEBUG] 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X\n",
                            p_psram_ptr[0], p_psram_ptr[1], p_psram_ptr[2], p_psram_ptr[3], p_psram_ptr[4], p_psram_ptr[5]);
            heap_print(HEAP_PSRAM);
            DBG_PRINTF("PSRAM malloc free\n");
            free((void *)p_psram_ptr);
            heap_print(HEAP_PSRAM);
            DBG_PRINTF("[DEBUG] PSRAM Test Success!\n");
        } else {
            DBG_PRINTF("[ERROR] PSRAM Test Failed\n");
        }
    }
}