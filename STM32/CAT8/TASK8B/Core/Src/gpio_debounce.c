#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
    uint8_t last_btn_state = GPIO_PIN_SET;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1) {
        uint8_t current_btn = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

        /* Detect press event (Falling Edge) */
        if (last_btn_state == GPIO_PIN_SET && current_btn == GPIO_PIN_RESET) {
            HAL_Delay(50); /* Contact bounce delay */
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                /* Wait for button release */
                while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET);
                HAL_Delay(20);
            }
        }
        last_btn_state = current_btn;
    }
}
