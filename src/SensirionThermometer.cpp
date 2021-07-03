#include "SensirionThermometer.h"

SensirionThermometer::SensirionThermometer(ThermoHygrometer *thermoHygrometer, const char label[])
{
    this->label = label;
    _thermoHygrometer = thermoHygrometer;
}

void SensirionThermometer::read()
{
    quant.sample(_thermoHygrometer->_sht20.readTemperature());
}
