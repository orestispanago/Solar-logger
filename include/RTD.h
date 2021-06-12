#ifndef RTD_h
#define RTD_h
#include <Wire.h>
#include <Adafruit_MAX31865.h>

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

class RTD
{
public:
    RTD(RTDType rtdType, numWires wires, int pin);
    float temperature();

private:
    Adafruit_MAX31865 *_max31865;
    float _rRef;
    float _rNominal;
    numWires _wires;
    void _begin();
};

#endif