#ifndef Logger_h
#define Logger_h

#include "Sensor.h"
#include "WiFiMQTTClient.h"
#include "ArduinoJson.h"
#include "Timer.h"

class Logger
{
public:
    Logger(Sensor **sensors, Timer *timer);
    void readAtInterval();
    void uploadAtInterval();
    void printAtInterval();
    void run();

private:
    Sensor **_sensors;
    WiFiMQTTClient _client;
    // unsigned long _currentMillis, _lastReadMillis, _lastUploadMillis;
    StaticJsonDocument<256> _jsonDoc;
    char _payload[256];
    void _update();
    void readAll();
    void _printPayload();
    Timer *_timer;
};
#endif