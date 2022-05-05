#ifndef Pyranometer_h
#define Pyranometer_h
#include <Adafruit_ADS1015.h>
#include "Sensor.h"

class Pyranometer : public Sensor
{
public:
    Pyranometer(const char label[]);
    void read();

private:
    uint _adsPin = 0;
    Adafruit_ADS1115 _ads;
    int16_t _adc0;
};

#endif