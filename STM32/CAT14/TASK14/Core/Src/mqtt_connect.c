#include "main.h"
#include "ESPLib.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

UART_HandleTypeDef huart2;

int main(void) {
    MQTT_InitTypeDef_t mqttSetting;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    /* 1. Initialize ESP8266 on USART2 */
    ESP8266_Init(StationMode, huart2);

    /* 2. Connect to Wi-Fi */
    ESP8266_wifiConnect("LabWiFi", "LabPassword123");

    /* 3. Connect to MQTT Broker */
    ESP8266_portConnect("TCP", "broker.emqx.io", "1883");

    /* 4. Configure and Connect MQTT Session */
    mqttSetting.keepAlive = 500;
    mqttSetting.connectFlag = CleanSession;
    mqttSetting.clientID = "STM32_Node_01";
    MQTT_connectBroker(&mqttSetting);

    while (1) {
        HAL_Delay(1000);
    }
}
