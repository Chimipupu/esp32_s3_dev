/**
 * @file pcb_define.h
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief 基板定義(YD-ESP32-S3)
 * @version 0.1
 * @date 2026-05-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#ifndef PCB_DEFINE_H
#define PCB_DEFINE_H

// -----------------------------------------------------------
// [コンパイルスイッチ]
#define PCB_YD_ESP32_S3

// -----------------------------------------------------------
#ifdef PCB_YD_ESP32_S3
// [基板定義(YD-ESP32-S3)]
// NOTE: ESP32-S3はI2C、I2SのGPIOを自由に割り当て可能
#define UART_0_TX_PIN     43 // UART0 TX  @GPIO 43
#define UART_0_RX_PIN     44 // UART0 RX  @GPIO 44
#define UART_1_TX_PIN     17 // UART0 TX  @GPIO 43
#define UART_1_RX_PIN     18 // UART0 RX  @GPIO 44
#define RGBLED_PIN        48 // RGBLED    @GPIO 48
#define BUTTON_PIN        46 // Button    @GPIO 41
#define SPI_MOSI_PIN      11 // SPI MOSI  @GPIO 11 (FSPID)
#define SPI_MISO_PIN      13 // SPI MISO  @GPIO 13 (FSPIQ)
#define SPI_SCK_PIN       12 // SPI CLK   @GPIO 12 (FSPICLK)
#define SPI_CS_PIN        10 // SPI CS/SS @GPIO 10 (FSPICS0)

// NOTE: ESP32-S3のUARTは5Mbpsが最大
// #define UART_BAUD         5000000 // UART @CH343P 5Mbps 8N1
// NOTE: 限界を超えてこそロマン！ESP32-S3のUARTを6Mbpsで動作
#define UART_BAUD         6000000 // UART @CH343P 6Mbps 8N1

#endif // PCB_YD_ESP32_S3

// -----------------------------------------------------------
// [DeepSleep]
#include "esp_sleep.h"
#define DEEPSLEEP_TIME_US_30SEC     (30ULL    * 1000000ULL) // DeepSleep @30秒
#define DEEPSLEEP_TIME_US_1MIN      (60ULL    * 1000000ULL) // DeepSleep @1分
#define DEEPSLEEP_TIME_US_2MIN      (120ULL   * 1000000ULL) // DeepSleep @2分
#define DEEPSLEEP_TIME_US_3MIN      (180ULL   * 1000000ULL) // DeepSleep @3分
#define DEEPSLEEP_TIME_US_5MIN      (300ULL   * 1000000ULL) // DeepSleep @5分
#define DEEPSLEEP_TIME_US_10MIN     (600ULL   * 1000000ULL) // DeepSleep @10分
#define DEEPSLEEP_TIME_US_15MIN     (900ULL   * 1000000ULL) // DeepSleep @15分
#define DEEPSLEEP_TIME_US_20MIN     (1200ULL  * 1000000ULL) // DeepSleep @20分
#define DEEPSLEEP_TIME_US_30MIN     (1800ULL  * 1000000ULL) // DeepSleep @30分
#define DEEPSLEEP_TIME_US_1HOUR     (3600ULL  * 1000000ULL) // DeepSleep @1時間
#define DEEPSLEEP_TIME_US_2HOUR     (7200ULL  * 1000000ULL) // DeepSleep @2時間
#define DEEPSLEEP_TIME_US_3HOUR     (10800ULL * 1000000ULL) // DeepSleep @3時間
#define DEEPSLEEP_TIME_US_5HOUR     (18000ULL * 1000000ULL) // DeepSleep @5時間
#define DEEPSLEEP_TIME_US_8HOUR     (28800ULL * 1000000ULL) // DeepSleep @8時間
#define DEEPSLEEP_TIME_US_12HOUR    (43200ULL * 1000000ULL) // DeepSleep @12時間
#define DEEPSLEEP_TIME_US_24HOUR    (86400ULL * 1000000ULL) // DeepSleep @24時間

#define DEEPSLEEP_TIME_US           DEEPSLEEP_TIME_US_1MIN

// -----------------------------------------------------------

#endif // PCB_DEFINE_H