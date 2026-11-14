#ifndef ESPLIB_H_
#define ESPLIB_H_

#include "main.h"

typedef enum {
    StationMode = 1,
    APMode = 2,
    CombinedMode = 3
} WiFiMode_t;

typedef enum {
    CleanSession = 0x02,
    KeepSession = 0x00
} MQTTConnectFlag_t;

typedef enum {
    QoS0 = 0,
    QoS1 = 1,
    QoS2 = 2
} MQTT_QoS_t;

typedef struct {
    uint16_t keepAlive;
    MQTTConnectFlag_t connectFlag;
    char *clientID;
} MQTT_InitTypeDef_t;

void ESP8266_Init(WiFiMode_t mode, UART_HandleTypeDef uart);
void ESP8266_wifiConnect(char *ssid, char *pass);
void ESP8266_portConnect(char *protocol, char *host, char *port);
void MQTT_connectBroker(MQTT_InitTypeDef_t *setting);
void MQTT_publishTopic(char *topic, char *payload, MQTT_QoS_t qos);
void MQTT_subscribeTopic(char *topic, uint8_t qos);
void MQTTDataHandler(char *topic, char *data);
void MQTTTimer(void);

#endif
