#ifndef Logger_h
#define Logger_h

#include "Sensor.h"
#include "WiFiMQTTClient.h"
#include "ArduinoJson.h"

class Logger
{
public:
    Logger(Sensor **sensors);
    void readAtInterval(unsigned long readIinterval);
    void uploadAtInterval(unsigned long uploadInterval);
    void printAtInterval(unsigned long uploadInterval);
    void run(unsigned long readInterval, unsigned long uploadInterval);

private:
    Sensor **_sensors;
    WiFiMQTTClient _client;
    unsigned long _currentMillis, _lastReadMillis, _lastUploadMillis;
    StaticJsonDocument<256> _jsonDoc;
    char _payload[256];
    void _update();
    void readAll();
    void _printPayload();
};
#endif