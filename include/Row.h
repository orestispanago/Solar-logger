#ifndef Row_h
#define Row_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Quantity.h"

class Row
{
public:
    Row(Quantity *quantities, int size);
    void update();
    void print();
    void readAll();
    char *payload();
    StaticJsonDocument<256> _jsonDoc;

private:
    Quantity *_quantities;
    int _numQuantities;
    char _payload[256];
};
#endif