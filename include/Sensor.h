#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include "Measurement.h"

class Sensor
{
public:
    Sensor();
    virtual void read();
    Measurement measurement;
    const char *label;
    static int count;
};
#endif