/**
 * @file app_wifi.h
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief WiFiアプリ
 * @version 0.1
 * @date 2026-05-18
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#ifndef APP_WIFI_H
#define APP_WIFI_H

#include <Arduino.h>
#include "WiFi.h"

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// -----------------------------------------------------------
typedef struct {
    wifi_auth_mode_t auth_mode;
    char *p_auth_str;
} app_wifi_auth_data_t;

extern const app_wifi_auth_data_t g_wifi_auth_data_tbl[];
extern const uint8_t WIFI_AUTH_DATA_TBL_SIZE;

// -----------------------------------------------------------
void app_wifi_scan(void);
void app_wifi_init(void);
void app_wifi_main(void);

#endif // APP_WIFI_H