#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include "Measurement.h"

class Sensor
{
public:
    Sensor();
    virtual void read() = 0; // = 0 means read() is not implemented (makes class abstract)
    Measurement measurement;
    const char *label;
};
#endif