/**
 * @file app_file_system.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief ファイルシステムのアプリ
 * @version 0.1
 * @date 2026-05-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#include "app_file_system.hpp"

#define BUF_MAX_SIZE    (1024 * 32)

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
        heap_print(HEAP_PSRAM);
    } else {
        DBG_PRINTF("This ESP32 is PSRAM does not exist\n");
    }
}

#ifdef SYSTEM_RAM_TEST
static void ram_test_proc(uint8_t *p_heap)
{
    uint32_t start_time, end_time;
    float time_ms;
    float speed_mbs;
    volatile uint8_t read_temp;
    uint32_t rand_idx = 0;
    uint32_t i;

    if (p_heap != NULL) {
        // --- Write Test (Sequential) ---
        start_time = micros();
        for (size_t i = 0; i < BUF_MAX_SIZE; i++) {
            p_heap[i] = (uint8_t)(i & 0xFF);
        }
        end_time = micros();

        time_ms = (end_time - start_time) / 1000.0;
        speed_mbs = (BUF_MAX_SIZE / 1024.0 / 1024.0) / (time_ms / 1000.0);
        DBG_PRINTF("  Write (Seq) : %.2f ms | Speed: %.2f MB/s\n", time_ms, speed_mbs);

        // --- Read Test (Sequential) ---
        start_time = micros();
        for (i = 0; i < BUF_MAX_SIZE; i++)
        {
            read_temp = p_heap[i];
        }
        end_time = micros();

        time_ms = (end_time - start_time) / 1000.0;
        speed_mbs = (BUF_MAX_SIZE / 1024.0 / 1024.0) / (time_ms / 1000.0);
        DBG_PRINTF("  Read  (Seq) : %.2f ms | Speed: %.2f MB/s\n", time_ms, speed_mbs);

        // --- Read Test (Random) ---
        rand_idx = 0;
        start_time = micros();
        for (i = 0; i < (BUF_MAX_SIZE / 2); i++)
        {
            rand_idx = (rand_idx + 2) & (BUF_MAX_SIZE - 1);
            read_temp = p_heap[rand_idx];
        }
        end_time = micros();

        time_ms = (end_time - start_time) / 1000.0;
        speed_mbs = (BUF_MAX_SIZE / 1024.0 / 1024.0) / (time_ms / 1000.0);
        DBG_PRINTF("  Read  (Rand): %.2f ms | Speed: %.2f MB/s\n", time_ms, speed_mbs);

        free(p_heap);
    } else {
        DBG_PRINTF("Malloc Failed (Not enough heap)\n");
    }
}

/**
 * @brief RAMテスト(SRAMとPSRAM)
 * */
void app_fs_system_ram_test(void)
{
    uint8_t *p_heap = NULL;

    DBG_PRINTF("=====================================\n");
    DBG_PRINTF("   ESP32-S3 Memory Benchmark (Size: %d KB)\n", BUF_MAX_SIZE / 1024);
    DBG_PRINTF("=====================================\n");

    DBG_PRINTF("[SRAM Test]\n");
    p_heap = (uint8_t *)heap_caps_malloc(BUF_MAX_SIZE, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    ram_test_proc(p_heap);

    DBG_PRINTF("-------------------------------------\n");
    s_is_psram = psramFound();
    if (s_is_psram) {
        DBG_PRINTF("[PSRAM Test]\n");
        p_heap = (uint8_t *)app_fs_heap_malloc(BUF_MAX_SIZE, HEAP_PSRAM_8BIT);
        ram_test_proc(p_heap);
    }

    DBG_PRINTF("=====================================\n");
}
#endif // SYSTEM_RAM_TEST