#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

typedef enum {
    STATE_TOGGLE = 0,
    STATE_BLINK
} AppState_t;

int main(void) {
    AppState_t state = STATE_TOGGLE;
    uint32_t t_press = 0;
    uint8_t btn_active = 0;
    uint32_t t_last_blink = 0;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1) {
        uint32_t t_now = HAL_GetTick();

        /* Sample Button (PA0 with internal pull-up) */
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) {
            if (!btn_active) {
                btn_active = 1;
                t_press = t_now;
            }
        } else {
            if (btn_active) {
                uint32_t duration = t_now - t_press;
                btn_active = 0;

                if (duration >= 50) { /* Debounce threshold */
                    if (duration < 1000) {
                        /* Short Press (< 1 second) */
                        if (state == STATE_BLINK) {
                            state = STATE_TOGGLE; /* Stop blinking */
                        } else {
                            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                        }
                    } else {
                        /* Long Press (>= 1 second) */
                        state = STATE_BLINK; /* Continuous blinking */
                    }
                }
            }
        }

        /* Non-blocking background blink handler */
        if (state == STATE_BLINK) {
            if (t_now - t_last_blink >= 250) {
                t_last_blink = t_now;
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            }
        }
    }
}
