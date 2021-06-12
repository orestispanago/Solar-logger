#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>

class Sensor
{
public:
    Sensor();
    virtual float read();
};
#endif