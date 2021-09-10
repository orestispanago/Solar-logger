#include "LoggerService.h"

LoggerService::LoggerService(Sensor **sensors, Timer *timer, int numSensors)
{
    _sensors = sensors;
    _timer = timer;
    _numSensors = numSensors;
}

void LoggerService::_readAtInterval()
{
    _timer->currentMillis = millis();
    if (_timer->currentMillis - _timer->lastReadMillis >= _timer->readInterval)
    {
        _readAll();
        _timer->lastReadMillis = _timer->currentMillis;
    }
}
void LoggerService::_uploadAtInterval()
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
void LoggerService::_update()
{
    _jsonDoc["count"] = _sensors[0]->measurement.count();
    for (int i = 0; i < _numSensors; i++)
    {
        _jsonDoc[_sensors[i]->label] = _sensors[i]->measurement.mean();
    }
    //   client.jsonDoc["heapUsage"] = getHeapUsage();
    serializeJson(_jsonDoc, _payload);
}
void LoggerService::_readAll()
{
    for (int i = 0; i < _numSensors; i++)
    {
        _sensors[i]->read();
    }
}
void LoggerService::_printPayload()
{
    serializeJson(_jsonDoc, Serial);
    Serial.println();
}
void LoggerService::run()
{
    if (_connectionService.isConnected())
    {
        _readAtInterval();
        _uploadAtInterval();
        _connectionService.loop();
    }
}
