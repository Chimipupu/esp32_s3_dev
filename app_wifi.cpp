/**
 * @file app_wifi.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief WiFiアプリ
 * @version 0.1
 * @date 2026-05-18
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#include "app_wifi.h"
#include "time.h"

// -----------------------------------------------------------
typedef struct {
    wifi_auth_mode_t auth_mode;
    char *p_auth_str;
} app_wifi_auth_data_t;

static const char *gp_ntp_server_tbl[] = {
    "ntp.nict.jp",
    "time.google.com",
    "ntp.jst.mfeed.ad.jp",
};

static const app_wifi_auth_data_t g_wifi_auth_data_tbl[] = {
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
static const uint8_t WIFI_AUTH_DATA_TBL_SIZE = sizeof(g_wifi_auth_data_tbl) / sizeof(g_wifi_auth_data_tbl[0]);

static time_t s_utc_time = 0;
static time_t s_jst_time = 0;
static struct tm *sp_utc_tm = NULL;
static struct tm *sp_jst_tm = NULL;

static bool s_is_wifi_connet = false;
static void _wifi_disconnet(void);
static bool _get_wifi_auth_mode_data(wifi_auth_mode_t auth_mode);
static void _get_ntp_time(void);
// -----------------------------------------------------------
// [Static]

static void _wifi_disconnet(void)
{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}

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

static void _get_ntp_time(void)
{
    struct tm utc_tm;
    struct tm jst_tm;

    // NTPに接続してUTCとJSTを取得
    configTime(NTP_TIMEZONE_JST, 0, gp_ntp_server_tbl[0], gp_ntp_server_tbl[1], gp_ntp_server_tbl[2]);
    s_utc_time = time(nullptr);
    sp_utc_tm = gmtime_r(&s_utc_time, &utc_tm);

    // NTPから同期が未完了なので表示せずに終了
    if(sp_utc_tm->tm_year <= 70) {
        return;
    }

    // UTCからJSTに変換
    sp_jst_tm = localtime_r(&s_utc_time, &jst_tm);

    // UTCとJSTを表示
    Serial.printf("UTC Time: %04d/%02d/%02d %02d:%02d:%02d\r\n",
        sp_utc_tm->tm_year + 1900, sp_utc_tm->tm_mon + 1, sp_utc_tm->tm_mday,
        sp_utc_tm->tm_hour, sp_utc_tm->tm_min, sp_utc_tm->tm_sec);
    Serial.printf("JST Time: %04d/%02d/%02d %02d:%02d:%02d\r\n",
        sp_jst_tm->tm_year + 1900, sp_jst_tm->tm_mon + 1, sp_jst_tm->tm_mday,
        sp_jst_tm->tm_hour, sp_jst_tm->tm_min, sp_jst_tm->tm_sec);
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

void app_wifi_init(const char *p_ssid, const char *p_password)
{
    if((p_ssid == NULL) && (p_password == NULL)) {
        WiFi.STA.begin();
        return;
    }

    if((p_ssid != NULL) && (p_password != NULL)) {
        WiFi.begin(p_ssid, p_password);
    }

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }

    s_is_wifi_connet = true;

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void app_wifi_main(void)
{
    // NTPから時刻取得
    _get_ntp_time();
}