#ifndef WiFiMQTTClient_h
#define WiFiMQTTClient_h
#include "Arduino.h"
#include <WiFi.h>
#include <MQTTClient.h> // MQTT Client from Joël Gaehwiler https://github.com/256dpi/arduino-mqtt   keepalive manually to 15s

class WiFiMQTTClient
{
public:
    WiFiMQTTClient();
    boolean connected();
    void upload(char *payload);
    void loop();

private:
    uint8_t status;
    unsigned long waitCount;
    WiFiClient espClient;
    String clientId;
};

#endif