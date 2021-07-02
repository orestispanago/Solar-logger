#include "Row.h"

Row::Row(Quantity *quantities, int size)
{
    _quantities = quantities;
    _numQuantities = size;
}

void Row::update()
{
    _jsonDoc["count"] = _quantities[0].count();
    for (int i = 0; i < _numQuantities; i++)
    {
        _jsonDoc[_quantities[i].label] = _quantities[i].mean();
    }
    //   client.jsonDoc["heapUsage"] = getHeapUsage();
}

void Row::print()
{
    serializeJson(_jsonDoc, Serial);
    Serial.println();
}

void Row::readAll()
{
    for (int i = 0; i < _numQuantities; i++)
    {
        _quantities[i].sample();
    }
}

char *Row::payload()
{
    serializeJson(_jsonDoc, _payload);
    return _payload;
}
