#include "ESPLib.h"
#include <string.h>
#include <stdio.h>

static UART_HandleTypeDef esp_uart;
static volatile uint32_t mqtt_timer_tick = 0;
static uint16_t mqtt_keep_alive_s = 60;

static void send_cmd(const char *cmd, uint32_t delay_ms) {
    HAL_UART_Transmit(&esp_uart, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_Delay(delay_ms);
}

void ESP8266_Init(WiFiMode_t mode, UART_HandleTypeDef uart) {
    esp_uart = uart;
    send_cmd("AT\r\n", 300);
    send_cmd("ATE0\r\n", 200); /* Disable echo for cleaner parsing */

    char mode_cmd[32];
    snprintf(mode_cmd, sizeof(mode_cmd), "AT+CWMODE=%d\r\n", (int)mode);
    send_cmd(mode_cmd, 500);
}

void ESP8266_wifiConnect(char *ssid, char *pass) {
    char conn_cmd[128];
    snprintf(conn_cmd, sizeof(conn_cmd), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, pass);
    send_cmd(conn_cmd, 5000); /* Allow up to 5s for DHCP lease */
}

void ESP8266_portConnect(char *protocol, char *host, char *port) {
    char sock_cmd[128];
    snprintf(sock_cmd, sizeof(sock_cmd), "AT+CIPSTART=\"%s\",\"%s\",%s\r\n", protocol, host, port);
    send_cmd(sock_cmd, 3000);
}

void MQTT_connectBroker(MQTT_InitTypeDef_t *setting) {
    if (setting == NULL) return;
    mqtt_keep_alive_s = setting->keepAlive;

    /* Build standard MQTT 3.1.1 CONNECT packet */
    uint8_t packet[128];
    uint16_t client_id_len = strlen(setting->clientID);
    uint16_t var_hdr_len = 10;
    uint16_t payload_len = 2 + client_id_len;
    uint16_t rem_len = var_hdr_len + payload_len;

    int idx = 0;
    packet[idx++] = 0x10; /* CONNECT Control Packet */
    packet[idx++] = (uint8_t)rem_len;

    /* Variable Header: Protocol Name "MQTT", Level 4 (v3.1.1) */
    packet[idx++] = 0x00; packet[idx++] = 0x04;
    packet[idx++] = 'M'; packet[idx++] = 'Q'; packet[idx++] = 'T'; packet[idx++] = 'T';
    packet[idx++] = 0x04; /* Level 4 */
    packet[idx++] = (uint8_t)setting->connectFlag;
    packet[idx++] = (uint8_t)(setting->keepAlive >> 8);
    packet[idx++] = (uint8_t)(setting->keepAlive & 0xFF);

    /* Payload: Client ID */
    packet[idx++] = (uint8_t)(client_id_len >> 8);
    packet[idx++] = (uint8_t)(client_id_len & 0xFF);
    memcpy(&packet[idx], setting->clientID, client_id_len);
    idx += client_id_len;

    /* Send via AT+CIPSEND */
    char send_cmd_buf[32];
    snprintf(send_cmd_buf, sizeof(send_cmd_buf), "AT+CIPSEND=%d\r\n", idx);
    send_cmd(send_cmd_buf, 200);

    HAL_UART_Transmit(&esp_uart, packet, idx, HAL_MAX_DELAY);
    HAL_Delay(1000);
}

void MQTT_publishTopic(char *topic, char *payload, MQTT_QoS_t qos) {
    if (topic == NULL || payload == NULL) return;

    uint8_t packet[256];
    uint16_t topic_len = strlen(topic);
    uint16_t payload_len = strlen(payload);
    uint16_t rem_len = 2 + topic_len + payload_len;

    int idx = 0;
    packet[idx++] = 0x30 | ((uint8_t)qos << 1); /* PUBLISH */
    packet[idx++] = (uint8_t)rem_len;

    /* Topic */
    packet[idx++] = (uint8_t)(topic_len >> 8);
    packet[idx++] = (uint8_t)(topic_len & 0xFF);
    memcpy(&packet[idx], topic, topic_len);
    idx += topic_len;

    /* Payload */
    memcpy(&packet[idx], payload, payload_len);
    idx += payload_len;

    char send_cmd_buf[32];
    snprintf(send_cmd_buf, sizeof(send_cmd_buf), "AT+CIPSEND=%d\r\n", idx);
    send_cmd(send_cmd_buf, 100);

    HAL_UART_Transmit(&esp_uart, packet, idx, HAL_MAX_DELAY);
    HAL_Delay(100);
}

void MQTT_subscribeTopic(char *topic, uint8_t qos) {
    if (topic == NULL) return;

    uint8_t packet[128];
    uint16_t topic_len = strlen(topic);
    uint16_t rem_len = 2 + (2 + topic_len + 1);

    int idx = 0;
    packet[idx++] = 0x82; /* SUBSCRIBE */
    packet[idx++] = (uint8_t)rem_len;

    /* Packet Identifier */
    packet[idx++] = 0x00; packet[idx++] = 0x01;

    /* Topic */
    packet[idx++] = (uint8_t)(topic_len >> 8);
    packet[idx++] = (uint8_t)(topic_len & 0xFF);
    memcpy(&packet[idx], topic, topic_len);
    idx += topic_len;

    /* Requested QoS */
    packet[idx++] = qos;

    char send_cmd_buf[32];
    snprintf(send_cmd_buf, sizeof(send_cmd_buf), "AT+CIPSEND=%d\r\n", idx);
    send_cmd(send_cmd_buf, 100);

    HAL_UART_Transmit(&esp_uart, packet, idx, HAL_MAX_DELAY);
    HAL_Delay(500);
}

void MQTTDataHandler(char *topic, char *data) {
    /* Polls incoming ESP8266 serial buffer for MQTT PUBLISH packets */
    uint8_t rx_byte;
    static char rx_buf[128];
    static uint16_t rx_idx = 0;

    if (HAL_UART_Receive(&esp_uart, &rx_byte, 1, 10) == HAL_OK) {
        if (rx_idx < sizeof(rx_buf) - 1) {
            rx_buf[rx_idx++] = rx_byte;
            rx_buf[rx_idx] = '\0';
        }

        /* Check for +IPD header */
        char *ipd = strstr(rx_buf, "+IPD,");
        if (ipd != NULL) {
            char *colon = strchr(ipd, ':');
            if (colon != NULL) {
                /* Packet payload starts after colon */
                uint8_t *mqtt_pkt = (uint8_t*)(colon + 1);
                if ((mqtt_pkt[0] & 0xF0) == 0x30) { /* MQTT PUBLISH packet */
                    uint16_t t_len = (mqtt_pkt[2] << 8) | mqtt_pkt[3];
                    if (topic != NULL && t_len < 32) {
                        strncpy(topic, (char*)&mqtt_pkt[4], t_len);
                        topic[t_len] = '\0';
                    }
                    if (data != NULL) {
                        uint8_t rem = mqtt_pkt[1];
                        uint16_t p_len = rem - 2 - t_len;
                        if (p_len < 64) {
                            strncpy(data, (char*)&mqtt_pkt[4 + t_len], p_len);
                            data[p_len] = '\0';
                        }
                    }
                }
                rx_idx = 0;
                memset(rx_buf, 0, sizeof(rx_buf));
            }
        }
        if (rx_idx >= sizeof(rx_buf) - 1) {
            rx_idx = 0;
        }
    }
}

void MQTTTimer(void) {
    mqtt_timer_tick++;
    /* Send periodic MQTT PINGREQ every keep_alive_s / 2 seconds */
    if (mqtt_timer_tick >= ((uint32_t)mqtt_keep_alive_s * 500)) {
        mqtt_timer_tick = 0;
        uint8_t ping_pkt[2] = { 0xC0, 0x00 }; /* PINGREQ */
        char send_cmd_buf[32];
        snprintf(send_cmd_buf, sizeof(send_cmd_buf), "AT+CIPSEND=2\r\n");
        HAL_UART_Transmit(&esp_uart, (uint8_t*)send_cmd_buf, strlen(send_cmd_buf), 50);
        HAL_Delay(50);
        HAL_UART_Transmit(&esp_uart, ping_pkt, 2, 50);
    }
}
