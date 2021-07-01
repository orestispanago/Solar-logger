#include "SensirionThermometer.h"

SensirionThermometer::SensirionThermometer(ThermoHygrometer *thermoHygrometer)
{
    _thermoHygrometer = thermoHygrometer;
}

float SensirionThermometer::read()
{
    return _thermoHygrometer->_sht20.readTemperature();
}
