#ifndef thermometers_h
#define thermometers_h

#include <Wire.h>
#include <Adafruit_MAX31865.h>


class Thermometers
{
public:
    Thermometers();
    void read();
    void print();
    int getNumber();
    float* getTempValues();
};

#endif
