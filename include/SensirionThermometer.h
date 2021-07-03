#ifndef Thermo_h
#define Thermo_h
#include "ThermoHygrometer.h"

class SensirionThermometer : public Sensor
{
public:
    SensirionThermometer(ThermoHygrometer *thermoHygrometer, const char label[]);
    void read();

private:
    ThermoHygrometer *_thermoHygrometer;
};

#endif