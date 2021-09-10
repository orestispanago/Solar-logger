#ifndef LoggerService_h
#define LoggerService_h

#include "Sensor.h"
#include "ConnectionService.h"
#include "ArduinoJson.h"
#include "Timer.h"

class LoggerService
{
public:
    LoggerService(Sensor **sensors, Timer *timer, int numSensors);
    void run();

private:
    Sensor **_sensors;
    Timer *_timer;
    ConnectionService _connectionService;
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