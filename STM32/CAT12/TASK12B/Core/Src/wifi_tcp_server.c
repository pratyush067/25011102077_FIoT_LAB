#include "main.h"
#include <stdio.h>
#include <string.h>

/* USART and System Prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

UART_HandleTypeDef huart1; /* PC Debug Console (115200 bps) */
UART_HandleTypeDef huart2; /* ESP8266 Wi-Fi Modem (115200 bps) */

static char rx_buffer[512];
static char tx_buffer[256];

/**
  * @brief Transmit AT command to ESP8266 and wait for execution
  */
void send_at(const char *cmd, uint32_t delay_ms) {
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_Delay(delay_ms);
}

/**
  * @brief Send HTTP response to connected client via ESP8266 AT+CIPSEND
  * @param link_id Active connection ID (0-4)
  */
void send_http_response(uint8_t link_id) {
    char http_body[128];
    char http_response[384];
    char cmd[32];

    /* Prepare HTML Body */
    snprintf(http_body, sizeof(http_body),
             "<html><body><h1>STM32 IoT Node</h1><p>Hello from STM32 HTTP Server</p></body></html>\r\n");
    int body_len = strlen(http_body);

    /* Construct Full HTTP 1.1 Response */
    snprintf(http_response, sizeof(http_response),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %d\r\n"
             "Connection: close\r\n\r\n"
             "%s",
             body_len, http_body);
    int total_len = strlen(http_response);

    /* Step 1: Send CIPSEND command specifying client ID and payload length */
    snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%d,%d\r\n", link_id, total_len);
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_Delay(200);

    /* Step 2: Transmit HTTP payload upon prompt */
    HAL_UART_Transmit(&huart2, (uint8_t*)http_response, total_len, HAL_MAX_DELAY);
    HAL_Delay(200);

    /* Step 3: Close connection */
    snprintf(cmd, sizeof(cmd), "AT+CIPCLOSE=%d\r\n", link_id);
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_Delay(100);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    /* Task 10C: Configure ESP8266 as a TCP Server */
    send_at("AT\r\n", 500);
    send_at("AT+CWMODE=1\r\n", 500);
    send_at("AT+CWJAP=\"LabWiFi\",\"Password123\"\r\n", 5000);
    send_at("AT+CIFSR\r\n", 1000);
    send_at("AT+CIPMUX=1\r\n", 500);
    send_at("AT+CIPSERVER=1,80\r\n", 500);

    /* Task 10D: Listen for HTTP Request in +IPD frame and send response */
    while (1) {
        uint8_t ch;
        int idx = 0;
        memset(rx_buffer, 0, sizeof(rx_buffer));

        while (HAL_UART_Receive(&huart2, &ch, 1, 50) == HAL_OK && idx < sizeof(rx_buffer) - 1) {
            rx_buffer[idx++] = ch;
            /* Echo to debug console */
            HAL_UART_Transmit(&huart1, &ch, 1, 10);
        }

        /* Check for incoming +IPD frame: +IPD,<link_id>,<len>:GET / HTTP/1.1 */
        char *ipd = strstr(rx_buffer, "+IPD,");
        if (ipd != NULL) {
            uint8_t link_id = ipd[5] - '0';
            if (strstr(rx_buffer, "GET") != NULL) {
                send_http_response(link_id);
            }
        }
    }
}
