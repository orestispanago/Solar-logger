#include "SensirionHygrometer.h"

SensirionHygrometer::SensirionHygrometer(ThermoHygrometer *thermoHygrometer, const char label[])
{
    this->label = label;
    _thermoHygrometer = thermoHygrometer;
}

void SensirionHygrometer::read()
{
    measurement.sample(_thermoHygrometer->_sht20.readHumidity());
}
