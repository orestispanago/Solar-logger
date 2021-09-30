#ifndef ConnectionService_h
#define ConnectionService_h
#include <WiFi.h>
#include <MQTTClient.h> // MQTT Client from Joël Gaehwiler https://github.com/256dpi/arduino-mqtt   keepalive manually to 15s

const int MESSAGE_SIZE = 1024;

class ConnectionService
{
public:
    ConnectionService();
    boolean isConnected();
    void upload(char *payload);
    void loop();

private:
    uint8_t status;
    unsigned long waitCount;
    WiFiClient espClient;
    String clientId;
};

#endif