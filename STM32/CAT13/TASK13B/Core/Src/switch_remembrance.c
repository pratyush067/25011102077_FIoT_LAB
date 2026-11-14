#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
    uint8_t led_latch = 0;
    uint8_t prev_switch = GPIO_PIN_SET;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1) {
        uint8_t curr_switch = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

        if (prev_switch == GPIO_PIN_SET && curr_switch == GPIO_PIN_RESET) {
            HAL_Delay(40); /* Debounce */
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
                led_latch = !led_latch; /* Invert latched state */
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, led_latch ? GPIO_PIN_SET : GPIO_PIN_RESET);

                while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET);
                HAL_Delay(20);
            }
        }
        prev_switch = curr_switch;
    }
}
