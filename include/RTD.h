#ifndef RTD_h
#define RTD_h
#include <Wire.h>
#include <Adafruit_MAX31865.h>
#include "Sensor.h"

enum RTDType
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

class RTD : public Sensor
{
public:
    RTD(RTDType rtdType, numWires wires, int pin);
    float read();

private:
    Adafruit_MAX31865 *_max31865;
    float _rRef;
    float _rNominal;
    numWires _wires;
    void _begin();
};

#endif