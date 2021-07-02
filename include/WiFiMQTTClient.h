#ifndef WiFiMQTTClient_h
#define WiFiMQTTClient_h
#include "Arduino.h"
#include <WiFi.h>
#include <MQTTClient.h> // MQTT Client from Joël Gaehwiler https://github.com/256dpi/arduino-mqtt   keepalive manually to 15s
#include "Row.h"

class WiFiMQTTClient
{
public:
    WiFiMQTTClient();
    boolean connected();
    void upload(Row row);
    void loop();
    StaticJsonDocument<256> jsonDoc;
    char payload[256];

private:
    int16_t messageSize = 256;
    // MQTTClient mqttClient;
    uint8_t status;
    unsigned long waitCount;
    WiFiClient espClient;
    String clientId;
};

#endif