#ifndef PT_h
#define PT_h
#include <Wire.h>
#include <Adafruit_MAX31865.h>
#include "Sensor.h"


enum numWires
{
    TWO_WIRE,
    THREE_WIRE,
    FOUR_WIRE
};

class PT : public Sensor
{
public:
    PT(int rNominal, numWires wires, int pin, const char label[]);
    void read();

private:
    Adafruit_MAX31865 *_max31865;
    float _rRef;
    float _rNominal;
    numWires _wires;
    void _begin();
};

#endif