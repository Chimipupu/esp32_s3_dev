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

#define UART_BAUD         6000000 // UART @CH343P 6Mbps 8N1
#endif // PCB_YD_ESP32_S3

// -----------------------------------------------------------

#endif // PCB_DEFINE_H