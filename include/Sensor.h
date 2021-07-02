#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include "Quantity.h"

class Sensor
{
public:
    Sensor();
    virtual void read();
    Quantity quant;
    const char *label;
};
#endif