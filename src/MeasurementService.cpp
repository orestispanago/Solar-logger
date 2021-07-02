#include "MeasurementService.h"

MeasurementService::MeasurementService(Row *row, WiFiMQTTClient *client)
{
    _row = row;
    _client = client;
}

void MeasurementService::readAtInterval(unsigned long readInterval)
{
    _currentMillis = millis();
    if (_currentMillis - _lastReadMillis >= readInterval)
    {
        _lastReadMillis = _currentMillis;
        _row->readAll();
        _row->print();
    }
}
// void MeasurementService::uploadAtInterval(unsigned long uploadInterval)
// {
//     _currentMillis = millis();
//     if (_currentMillis - _lastReadMillis >= uploadInterval)
//     {
//         _lastUploadMillis = _currentMillis;
//         _row->update();
//         _row->print();
//         _client->upload(_row);
//     }
// }