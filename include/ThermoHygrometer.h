#ifndef ThermoHygrometer_h
#define ThermoHygrometer_h

#include <Wire.h>
#include "DFRobot_SHT20.h"

class ThermoHygrometer
{
public:
    ThermoHygrometer();
    float temperature();
    float humidity();

private:
    DFRobot_SHT20 _sht20;
    void _init();
};

#endif