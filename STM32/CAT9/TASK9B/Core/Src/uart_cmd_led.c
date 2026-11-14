#include "main.h"
#include <string.h>

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

UART_HandleTypeDef huart1;

static void uart_send_str(const char *s) {
    HAL_UART_Transmit(&huart1, (uint8_t*)s, strlen(s), HAL_MAX_DELAY);
}

int main(void) {
    char cmd_buffer[32];
    uint8_t idx = 0;
    uint8_t ch;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    uart_send_str("\r\n=== STM32 CLI Command Interface ===\r\n");
    uart_send_str("Commands: LED ON | LED OFF | LED TOGGLE\r\n> ");

    while (1) {
        if (HAL_UART_Receive(&huart1, &ch, 1, 100) == HAL_OK) {
            HAL_UART_Transmit(&huart1, &ch, 1, 10); /* Echo */

            if (ch == '\r' || ch == '\n') {
                if (idx > 0) {
                    cmd_buffer[idx] = '\0';

                    if (strcmp(cmd_buffer, "LED ON") == 0) {
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
                        uart_send_str("\r\nLED turned ON\r\n> ");
                    } else if (strcmp(cmd_buffer, "LED OFF") == 0) {
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
                        uart_send_str("\r\nLED turned OFF\r\n> ");
                    } else if (strcmp(cmd_buffer, "LED TOGGLE") == 0) {
                        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                        uart_send_str("\r\nLED toggled\r\n> ");
                    } else {
                        uart_send_str("\r\nError: Unrecognized command\r\n> ");
                    }
                    idx = 0;
                }
            } else if (idx < sizeof(cmd_buffer) - 1) {
                cmd_buffer[idx++] = ch;
            }
        }
    }
}
