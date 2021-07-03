#include "Logger.h"

Logger::Logger(Sensor **sensors)
{
    _sensors = sensors;
}

void Logger::readAtInterval(unsigned long readInterval)
{
    _currentMillis = millis();
    if (_currentMillis - _lastReadMillis >= readInterval)
    {
        _lastReadMillis = _currentMillis;
        readAll();
    }
}
void Logger::uploadAtInterval(unsigned long uploadInterval)
{
    _currentMillis = millis();
    if (_currentMillis - _lastUploadMillis >= uploadInterval)
    {
        _lastUploadMillis = _currentMillis;
        _update();
        _client.upload(_payload);
    }
}
void Logger::_update()
{
    _jsonDoc["count"] = _sensors[0]->quant.count();
    for (int i = 0; i < _sensors[0]->count; i++)
    {
        _jsonDoc[_sensors[i]->label] = _sensors[i]->quant.mean();
    }
    //   client.jsonDoc["heapUsage"] = getHeapUsage();
    serializeJson(_jsonDoc, _payload);
}
void Logger::readAll()
{
    for (int i = 0; i < _sensors[0]->count; i++)
    {
        _sensors[i]->read();
    }
}
void Logger::printPayload()
{
    serializeJson(_jsonDoc, _payload);
}
void Logger::run(unsigned long readInterval, unsigned long uploadInterval)
{
    if (_client.connected())
    {
        readAtInterval(readInterval);
        uploadAtInterval(uploadInterval);
        _client.loop();
    }
}
