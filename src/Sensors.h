#ifndef Sensors_h
#define Sensors_h

#include "RTD.h"
#include "Pyranometer.h"
#include "ThermoHygrometer.h"
#include "Measurement.h"

RTD therm1 = RTD(PT1000, FOUR_WIRE, 4);
RTD therm2 = RTD(PT1000, FOUR_WIRE, 5);
RTD therm3 = RTD(PT1000, FOUR_WIRE, 13);
RTD therm4 = RTD(PT1000, FOUR_WIRE, 14);
RTD therm5 = RTD(PT1000, FOUR_WIRE, 27);
RTD therm6 = RTD(PT1000, FOUR_WIRE, 26);
RTD therm7 = RTD(PT1000, FOUR_WIRE, 25);
RTD therm8 = RTD(PT1000, FOUR_WIRE, 33);
RTD therm9 = RTD(PT1000, FOUR_WIRE, 32);

ThermoHygrometer sht20;
Pyranometer pyranometer;

Measurement t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, h1, irr;

void readAll()
{
    t1.sample(therm1.temperature());
    t2.sample(therm2.temperature());
    t3.sample(therm3.temperature());
    t4.sample(therm4.temperature());
    t5.sample(therm5.temperature());
    t6.sample(therm6.temperature());
    t7.sample(therm7.temperature());
    t8.sample(therm8.temperature());
    t9.sample(therm9.temperature());
    t10.sample(sht20.temperature());
    h1.sample(sht20.humidity());
    irr.sample(pyranometer.voltage());
}

#endif