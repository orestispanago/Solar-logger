#ifndef PT_h
#define PT_h
#include <Wire.h>
#include <Adafruit_MAX31865.h>
#include "Sensor.h"


enum PTType
{
    PT100,
    PT1000
};

enum numWires
{
    TWO_WIRE,
    THREE_WIRE,
    FOUR_WIRE
};

class PT : public Sensor
{
public:
    PT(PTType rtdType, numWires wires, int pin, const char label[]);
    void read();

private:
    Adafruit_MAX31865 *_max31865;
    float _rRef;
    float _rNominal;
    numWires _wires;
    void _begin();
};

#endif