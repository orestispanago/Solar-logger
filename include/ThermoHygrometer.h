#ifndef ThermoHygrometer_h
#define ThermoHygrometer_h

#include <Wire.h>
#include "DFRobot_SHT20.h"
#include "Sensor.h"

class ThermoHygrometer : public Sensor
{
public:
    ThermoHygrometer();
    DFRobot_SHT20 _sht20;

private:
    void _init();
};

#endif