#include "ThermoHygrometer.h"
#include <Arduino.h>

ThermoHygrometer::ThermoHygrometer()
{
    DFRobot_SHT20 _sht20;
    _init();
}

void ThermoHygrometer::_init()
{
    _sht20.initSHT20();
    delay(100);
    _sht20.checkSHT20();
}
