/**
 * @file app_wifi.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief WiFiアプリ
 * @version 0.1
 * @date 2026-05-18
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#include "app_wifi.h"

// -----------------------------------------------------------
const app_wifi_auth_data_t g_wifi_auth_data_tbl[] = {
    {WIFI_AUTH_OPEN,            "open"},
    {WIFI_AUTH_WEP,             "WEP"},
    {WIFI_AUTH_WPA_PSK,         "WPA"},
    {WIFI_AUTH_WPA2_PSK,        "WPA2"},
    {WIFI_AUTH_WPA_WPA2_PSK,    "WPA+WPA2"},
    {WIFI_AUTH_WPA2_ENTERPRISE, "WPA2-EAP"},
    {WIFI_AUTH_WPA3_PSK,        "WPA3"},
    {WIFI_AUTH_WPA2_WPA3_PSK,   "WPA2+WPA3"},
    {WIFI_AUTH_WAPI_PSK,        "WAPI"},
};

const uint8_t WIFI_AUTH_DATA_TBL_SIZE = sizeof(g_wifi_auth_data_tbl) / sizeof(g_wifi_auth_data_tbl[0]);

static bool _get_wifi_auth_mode_data(wifi_auth_mode_t auth_mode);
// -----------------------------------------------------------
// [Static]

static bool _get_wifi_auth_mode_data(wifi_auth_mode_t auth_mode, app_wifi_auth_data_t *p_output_data)
{
    bool ret;
    uint8_t i;

    if(p_output_data == NULL) {
        return false;
    }

    ret = false;
    p_output_data->p_auth_str = "none";

    for(i = 0; i < WIFI_AUTH_DATA_TBL_SIZE; i++)
    {
        if(g_wifi_auth_data_tbl[i].auth_mode == auth_mode) {
            *p_output_data = g_wifi_auth_data_tbl[i];
            ret = true;
        }
    }

    return ret;
}

// -----------------------------------------------------------
// [API]

void app_wifi_scan(void)
{
    uint8_t i;
    wifi_auth_mode_t wifi_auth_mode;
    uint8_t scan_cnt;
    app_wifi_auth_data_t wifi_auth_data;

    Serial.println("-------------------------------------");
    Serial.println("[WiFi Scan]");
    WiFi.setBandMode(WIFI_BAND_MODE_AUTO);

    scan_cnt = WiFi.scanNetworks();

    if (scan_cnt == 0) {
        Serial.println("WiFi not found");
    } else {
        Serial.printf("WiFi Found (%d)\r\n", scan_cnt);
        Serial.println("No | SSID                             | RSSI | CH | Encryption");

        for (i = 0; i < scan_cnt; ++i)
        {
            Serial.printf("%2d", i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4" PRIi32, WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2" PRIi32, WiFi.channel(i));
            Serial.print(" | ");

            wifi_auth_mode = WiFi.encryptionType(i);
            _get_wifi_auth_mode_data(wifi_auth_mode, &wifi_auth_data);
            Serial.printf("%s\r\n", wifi_auth_data.p_auth_str);

            delay(10);
        }
    }

    WiFi.scanDelete();
    Serial.println("-------------------------------------");
}

void app_wifi_init(void)
{
    WiFi.STA.begin();
}

void app_wifi_main(void)
{
    app_wifi_scan();
}