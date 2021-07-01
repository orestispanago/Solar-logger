#ifndef Thermo_h
#define Thermo_h
#include "ThermoHygrometer.h"

class SensirionThermometer : public Sensor
{
public:
    SensirionThermometer(ThermoHygrometer *thermoHygrometer);
    float read();

private:
    ThermoHygrometer *_thermoHygrometer;
};

#endif