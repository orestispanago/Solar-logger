#include "Logger.h"

Logger::Logger(Sensor **sensors, Timer *timer, int numSensors)
{
    _sensors = sensors;
    _timer = timer;
    _numSensors = numSensors;
    _appendCharacterToSensorLabels("S");
}

void Logger::_readAtInterval()
{
    _timer->currentMillis = millis();
    if (_timer->currentMillis - _timer->lastReadMillis >= _timer->readInterval)
    {
        _readAll();
        _timer->lastReadMillis = _timer->currentMillis;
    }
}
void Logger::_uploadAtInterval()
{
    _timer->currentMillis = millis();
    if (_timer->currentMillis - _timer->lastUploadMillis >= _timer->uploadInterval)
    {
        _timer->lastUploadMillis = _timer->currentMillis;
        _update();
        // _printPayload();
        _connection.upload(_payload);
    }
}
void Logger::_update()
{
    _jsonDoc["count"] = _sensors[0]->measurement.count();
    for (int i = 0; i < _numSensors; i++)
    {
        _jsonDoc[_sensors[i]->label] = _sensors[i]->measurement.mean();
        _jsonDoc[_sensors[i]->labelS] = _sensors[i]->measurement.stdev();
    }
    serializeJson(_jsonDoc, _payload);
}
void Logger::_readAll()
{
    for (int i = 0; i < _numSensors; i++)
    {
        _sensors[i]->read();
    }
}
void Logger::_printPayload()
{
    serializeJson(_jsonDoc, Serial);
    Serial.println();
}
void Logger::run()
{
    if (_connection.statusOK())
    {
        _readAtInterval();
        _uploadAtInterval();
        _connection.loop();
    }
}
void Logger::_appendCharacterToSensorLabels(char character[2])
{
    for (int i = 0; i < _numSensors; i++)
    {
        strcpy(_sensors[i]->labelS, _sensors[i]->label);
        strcat(_sensors[i]->labelS, character);
    }
}