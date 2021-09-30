#ifndef Connection_h
#define Connection_h
#include <WiFi.h>
#include <MQTTClient.h> // MQTT Client from Joël Gaehwiler https://github.com/256dpi/arduino-mqtt   keepalive manually to 15s

const int MESSAGE_SIZE = 1024;

class Connection
{
public:
    Connection();
    boolean statusOK();
    void upload(char *payload);
    void loop();

private:
    uint8_t status;
    unsigned long waitCount;
    WiFiClient espClient;
    String clientId;
};

#endif