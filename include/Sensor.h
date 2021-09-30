#ifndef Sensor_h
#define Sensor_h

#include "Measurement.h"
#include <Arduino.h>

class Sensor
{
public:
    Sensor();
    virtual void read() = 0; // = 0 means read() is not implemented (makes class abstract)
    Measurement measurement;
    const char *label;
    char labelS[5]; // label + "S" character for stdev
};
#endif