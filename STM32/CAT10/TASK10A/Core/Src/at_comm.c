#include "main.h"
#include <string.h>

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

UART_HandleTypeDef huart1; /* PC Debug */
UART_HandleTypeDef huart2; /* Wemos ESP8266 */

int main(void) {
    uint8_t rx_byte;
    char at_ping[] = "AT\r\n";

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    /* Send AT command to ESP8266 */
    HAL_UART_Transmit(&huart2, (uint8_t*)at_ping, strlen(at_ping), HAL_MAX_DELAY);

    /* Bridge response to PC */
    while (1) {
        if (HAL_UART_Receive(&huart2, &rx_byte, 1, 10) == HAL_OK) {
            HAL_UART_Transmit(&huart1, &rx_byte, 1, 10);
        }
    }
}
