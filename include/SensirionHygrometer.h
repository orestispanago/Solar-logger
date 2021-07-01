#ifndef Hygro_h
#define Hygro_h
#include "ThermoHygrometer.h"

class SensirionHygrometer : public Sensor
{
public:
    SensirionHygrometer(ThermoHygrometer *thermoHygrometer);
    float read();

private:
    ThermoHygrometer *_thermoHygrometer;
};

#endif