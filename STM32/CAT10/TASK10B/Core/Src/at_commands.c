#include "main.h"
#include <string.h>

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

void send_cmd(const char *cmd) {
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_Delay(500);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    send_cmd("AT\r\n");
    send_cmd("AT+GMR\r\n");
    send_cmd("AT+CWMODE=1\r\n");
    send_cmd("AT+CIFSR\r\n");

    while (1);
}
