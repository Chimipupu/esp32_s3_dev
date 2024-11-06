/**
 * @file app_esp_now.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief ESPNOW アプリ
 * @version 0.1
 * @date 2024-11-6
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "app_esp_now.hpp"

esp_now_peer_info_t s_peer_info;
esp_now_send_status_t s_tx_status;
static bool s_is_rx_data = false;
static uint8_t s_rx_data_len = 0;
static uint8_t s_rx_data_buf[250] = {0};
static uint8_t s_tx_data_len = 0;
static uint8_t s_tx_data_buf[250] = {0};
static uint8_t s_my_mac_addr[6] = {0};
static uint8_t s_slave_mac_addr[6] = {0};
static uint8_t s_src_mac_addr[6] = {0};
static uint8_t s_des_mac_addr[6] = {0};
static char s_my_mac_str_buf[18] = {0};
static char s_slave_mac_str_buf[18] = {0};
static char s_src_mac_str_buf[18] = {0};
static char s_dst_mac_str_buf[18] = {0};

const uint8_t tx_data[13] = "CQCQCQ";
static void printMacAddr(esp_mac_type_t type);
static void scan_wifi_net_info(void);

void tx_proc_cbk(const uint8_t *p_mac_addr, esp_now_send_status_t status)
{
    __DI(&g_mux);
    snprintf(s_src_mac_str_buf, sizeof(s_src_mac_str_buf), "%02x:%02x:%02x:%02x:%02x:%02x",
            s_my_mac_addr[0], s_my_mac_addr[1], s_my_mac_addr[2],
            s_my_mac_addr[3], s_my_mac_addr[4], s_my_mac_addr[5]);

    snprintf(s_dst_mac_str_buf, sizeof(s_dst_mac_str_buf), "%02X:%02X:%02X:%02X:%02X:%02X",
            p_mac_addr[0], p_mac_addr[1], p_mac_addr[2], p_mac_addr[3], p_mac_addr[4], p_mac_addr[5]);

    s_tx_status = status;
    __EI(&g_mux);
}

void rx_proc_cbk(const esp_now_recv_info_t *p_info, const uint8_t *p_data, int data_len)
{
    __DI(&g_mux);
    memcpy(s_src_mac_addr, p_info->src_addr, 6);
    memcpy(s_des_mac_addr, p_info->des_addr, 6);

    snprintf(s_src_mac_str_buf, sizeof(s_src_mac_str_buf), "%02x:%02x:%02x:%02x:%02x:%02x",
            p_info->src_addr[0], p_info->src_addr[1], p_info->src_addr[2],
            p_info->src_addr[3], p_info->src_addr[4], p_info->src_addr[5]);

    snprintf(s_dst_mac_str_buf, sizeof(s_dst_mac_str_buf), "%02x:%02x:%02x:%02x:%02x:%02x",
            p_info->des_addr[0], p_info->des_addr[1], p_info->des_addr[2],
            p_info->des_addr[3], p_info->des_addr[4], p_info->des_addr[5]);

    snprintf(s_my_mac_str_buf, sizeof(s_my_mac_str_buf), "%02x:%02x:%02x:%02x:%02x:%02x",
            s_my_mac_addr[0], s_my_mac_addr[1], s_my_mac_addr[2],
            s_my_mac_addr[3], s_my_mac_addr[4], s_my_mac_addr[5]);

    s_rx_data_len = data_len;
    memset(&s_rx_data_buf, 0x00, sizeof(s_rx_data_buf));
    for (int i = 0; i < data_len; i++)
    {
        s_rx_data_buf[i] = *p_data;
        p_data++;
    }
    s_is_rx_data = true;

    __EI(&g_mux);
}

static void scan_wifi_net_info(void)
{
    DEBUG_PRINTF_RTOS("WiFi scan...\n");
    uint8_t network_cnt = WiFi.scanNetworks();

    if (network_cnt == 0) {
        DEBUG_PRINTF_RTOS("no WiFi network\n");
    } else {
        DEBUG_PRINTF_RTOS("found %d WiFi network\n", network_cnt);
        for (uint8_t i = 0; i < network_cnt; ++i) {
            DEBUG_PRINTF_RTOS("[WiFi Network No.%d]\n", i);
            String ssid = WiFi.SSID(i);
            DEBUG_PRINTF_RTOS("[SSID:%s] [RSSI:%d dBm] [Ch:%d]\n", ssid.c_str(), WiFi.RSSI(i), WiFi.channel(i));
        }
    }

    DEBUG_PRINTF_RTOS("");
}

void app_espnow_main(void)
{
#ifdef ESP_NOW_TX
    DEBUG_PRINTF_RTOS("TX Data : ");
    memset(&s_tx_data_buf, 0x00, sizeof(s_tx_data_buf));
    for (int i = 0; i < sizeof(tx_data); i++)
    {
        __DI(&g_mux);
        s_tx_data_buf[i] = tx_data[i];
        __EI(&g_mux);
        DEBUG_PRINTF_RTOS("%c", s_tx_data_buf[i]);
    }
    DEBUG_PRINTF_RTOS("\n");

    esp_err_t result = esp_now_send(s_peer_info.peer_addr, tx_data, sizeof(tx_data));

    DEBUG_PRINTF_RTOS("Send Status : ");
    if (result == ESP_OK) {
        DEBUG_PRINTF_RTOS("Success\n");
    } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
        DEBUG_PRINTF_RTOS("ESPNOW not Init\n");
    } else if (result == ESP_ERR_ESPNOW_ARG) {
        DEBUG_PRINTF_RTOS("Invalid Argument\n");
    } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
        DEBUG_PRINTF_RTOS("Internal Error\n");
    } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
        DEBUG_PRINTF_RTOS("ESP_ERR_ESPNOW_NO_MEM\n");
    } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
        DEBUG_PRINTF_RTOS("Peer not found\n");
    } else {
        DEBUG_PRINTF_RTOS("Not sure what happened\n");
    }

    DEBUG_PRINTF_RTOS("My MAC : %s\n", s_src_mac_str_buf);
    DEBUG_PRINTF_RTOS("Slave MAC : %s\n", s_slave_mac_str_buf);
    DEBUG_PRINTF_RTOS("Dest MAC : %s\n", s_dst_mac_str_buf);
    DEBUG_PRINTF_RTOS("TX Status : %s\n", s_tx_status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
#else
    if (s_is_rx_data != false) {
        DEBUG_PRINTF_RTOS("My MAC : %s\n", s_my_mac_str_buf);
        DEBUG_PRINTF_RTOS("Src MAC : %s\n", s_src_mac_str_buf);
        DEBUG_PRINTF_RTOS("Dest MAC : %s\n", s_dst_mac_str_buf);

        DEBUG_PRINTF_RTOS("RX Data Length : %d\n", s_rx_data_len);
        DEBUG_PRINTF_RTOS("RX Data : ");
        for (int i = 0; i < s_rx_data_len; i++)
        {
            DEBUG_PRINTF_RTOS("%c", s_rx_data_buf[i]);
        }
        DEBUG_PRINTF_RTOS("\n");

        s_is_rx_data = false;
    }
#endif /* ESP_NOW_TX */
}

static void printMacAddr(esp_mac_type_t type)
{
    uint8_t mac[6];

    esp_read_mac(mac, type);

    DEBUG_PRINTF_RTOS("%s MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                    type == ESP_MAC_WIFI_STA ? "WiFi STA" :
                    type == ESP_MAC_WIFI_SOFTAP ? "WiFi SoftAP" :
                    type == ESP_MAC_BT ? "Bluetooth" :
                    type == ESP_MAC_ETH ? "Ethernet" : "Unknown",
                    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void app_espnow_init(void)
{
    memset(&s_rx_data_buf, 0x00, sizeof(s_rx_data_buf));
    memset(&s_tx_data_buf, 0x00, sizeof(s_tx_data_buf));
    memset(&s_my_mac_addr, 0x00, sizeof(s_my_mac_addr));
    memset(&s_src_mac_addr, 0x00, sizeof(s_src_mac_addr));
    memset(&s_des_mac_addr, 0x00, sizeof(s_des_mac_addr));
    memset(&s_my_mac_str_buf, 0x00, sizeof(s_my_mac_str_buf));
    memset(&s_slave_mac_str_buf, 0x00, sizeof(s_slave_mac_str_buf));
    memset(&s_src_mac_str_buf, 0x00, sizeof(s_src_mac_str_buf));
    memset(&s_dst_mac_str_buf, 0x00, sizeof(s_dst_mac_str_buf));

#ifdef ESP_NOW_TX
    DEBUG_PRINTF_RTOS("ESPNow TX\n");
#else
    DEBUG_PRINTF_RTOS("ESPNow RX\n");
#endif

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    if (esp_now_init() == ESP_OK) {
        DEBUG_PRINTF_RTOS("ESPNow Init Success\n");
    } else {
        DEBUG_PRINTF_RTOS("ESPNow Init Failed\n");
        ESP.restart();
    }
    // printMacAddr(ESP_MAC_WIFI_STA);
    esp_read_mac(s_my_mac_addr, ESP_MAC_WIFI_STA);
    scan_wifi_net_info();

    // ブロードキャスト = MACアドレス FF:FF:FF:FF:FF:FF
    __DI(&g_mux);
    memset(&s_peer_info, 0, sizeof(s_peer_info));
    memset(&s_slave_mac_addr, 0xff, sizeof(s_slave_mac_addr));
    memcpy(s_peer_info.peer_addr, s_slave_mac_addr, 6);
    s_peer_info.channel = 0;
    s_peer_info.encrypt = false;
    snprintf(s_slave_mac_str_buf, sizeof(s_slave_mac_str_buf), "%02x:%02x:%02x:%02x:%02x:%02x",
            s_slave_mac_addr[0], s_slave_mac_addr[1], s_slave_mac_addr[2],
            s_slave_mac_addr[3], s_slave_mac_addr[4], s_slave_mac_addr[5]);
    __EI(&g_mux);

    esp_err_t addStatus = esp_now_add_peer(&s_peer_info);
    if (addStatus == ESP_OK) {
        DEBUG_PRINTF_RTOS("ESPNow Init OK\n");
    }

    esp_now_register_send_cb(tx_proc_cbk);
    esp_now_register_recv_cb(rx_proc_cbk);
}