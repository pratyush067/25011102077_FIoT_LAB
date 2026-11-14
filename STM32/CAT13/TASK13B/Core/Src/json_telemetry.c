#include "main.h"
#include <stdio.h>
#include <string.h>

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

UART_HandleTypeDef huart2;

void format_sensor_json(float temp, float hum, float press, char *output, size_t max_len) {
    snprintf(output, max_len,
             "{\"status\":\"success\",\"temperature\":%.2f,\"humidity\":%.2f,\"pressure\":%.2f}",
             temp, hum, press);
}

int main(void) {
    char json[150];
    float t = 28.45f, h = 62.30f, p = 1008.72f;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    while (1) {
        format_sensor_json(t, h, p, json, sizeof(json));
        HAL_UART_Transmit(&huart2, (uint8_t*)json, strlen(json), HAL_MAX_DELAY);
        HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);
        HAL_Delay(1000);
    }
}
