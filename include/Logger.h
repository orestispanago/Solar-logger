#ifndef Logger_h
#define Logger_h

#include "Sensor.h"
#include "WiFiMQTTClient.h"
#include "ArduinoJson.h"
#include "Timer.h"

class Logger
{
public:
    Logger(Sensor **sensors, Timer *timer, int numSensors);
    void run();

private:
    Sensor **_sensors;
    Timer *_timer;
    WiFiMQTTClient _client;
    StaticJsonDocument<256> _jsonDoc;
    char _payload[256];
    void _update();
    void _readAll();
    void _printPayload();
    void _readAtInterval();
    void _uploadAtInterval();
    int _numSensors;
};
#endif