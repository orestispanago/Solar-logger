#ifndef Sensors_h
#define Sensors_h

#include "RTD.h"
#include "Pyranometer.h"
#include "ThermoHygrometer.h"
#include "Measurement.h"
#include "SensorMeasurement.h"

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
SensorMeasurement irradiance = SensorMeasurement("irradiance", &pyranometer, &irr);

void resetMeasurements()
{
    t1.reset();
    t2.reset();
    t3.reset();
    t4.reset();
    t5.reset();
    t6.reset();
    t7.reset();
    t8.reset();
    t9.reset();
    t10.reset();
    h1.reset();
    irr.reset();
}

#endif