#include "main.h"
#include <string.h>

UART_HandleTypeDef huart1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

int main(void) {
    uint8_t rx_data;
    char welcome[] = "STM32 UART Initialized (115200-8-N-1)\r\nEcho active:\r\n";

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    HAL_UART_Transmit(&huart1, (uint8_t*)welcome, strlen(welcome), HAL_MAX_DELAY);

    while (1) {
        if (HAL_UART_Receive(&huart1, &rx_data, 1, 100) == HAL_OK) {
            HAL_UART_Transmit(&huart1, &rx_data, 1, 100);
        }
    }
}
