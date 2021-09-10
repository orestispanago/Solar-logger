#ifndef Hygro_h
#define Hygro_h
#include "ThermoHygrometer.h"

class SensirionHygrometer : public Sensor
{
public:
    SensirionHygrometer(ThermoHygrometer *thermoHygrometer, const char label[]);
    void read();

private:
    ThermoHygrometer *_thermoHygrometer;
};

#endif