#include "Logger.h"

Logger::Logger(Sensor **sensors, Timer *timer, int numSensors)
{
    _sensors = sensors;
    _timer = timer;
    _numSensors = numSensors;
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
        _printPayload();
        // _client.upload(_payload);
    }
}
void Logger::_update()
{
    _jsonDoc["count"] = _sensors[0]->measurement.count();
    for (int i = 0; i < _numSensors; i++)
    {
        _jsonDoc[_sensors[i]->label] = _sensors[i]->measurement.mean();
    }
    //   client.jsonDoc["heapUsage"] = getHeapUsage();
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
    if (_client.connected())
    {
        _readAtInterval();
        _uploadAtInterval();
        _client.loop();
    }
}
