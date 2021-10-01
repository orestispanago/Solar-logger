#ifndef Logger_h
#define Logger_h

#include "Sensor.h"
#include "Connection.h"
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
    Connection _connection;
    StaticJsonDocument<MESSAGE_SIZE> _jsonDoc;
    char _payload[MESSAGE_SIZE];
    void _update();
    void _readAll();
    void _printPayload();
    void _readAtInterval();
    void _uploadAtInterval();
    int _numSensors;
    void _appendCharacterToSensorLabels(char character[2]);
};
#endif