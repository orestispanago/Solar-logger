#include <Arduino.h>
#include "utils.h"
#include "RTD.h"
#include "Pyranometer.h"
#include "SensirionThermometer.h"
#include "SensirionHygrometer.h"
#include "Logger.h"
#include "Flowmeter.h"
#include "Timer.h"
#include "Anemometer.h"

unsigned long readInterval = 2000;
unsigned long uploadInterval = 10000;

RTD therm1(PT1000, FOUR_WIRE, 17, "ABD");
RTD therm2(PT1000, FOUR_WIRE, 16, "ABU");
RTD therm3(PT1000, FOUR_WIRE, 4, "AFD");
RTD therm4(PT1000, FOUR_WIRE, 0, "AFMD");

RTD therm5(PT1000, FOUR_WIRE, 32, "AFMU");
RTD therm6(PT1000, FOUR_WIRE, 33, "AFU");
RTD therm7(PT1000, FOUR_WIRE, 25, "IM");
// // RTD therm8(PT1000, FOUR_WIRE, 26);
RTD therm9(PT100, FOUR_WIRE, 27, "OUT");
RTD therm10(PT100, FOUR_WIRE, 14, "IN");

ThermoHygrometer sht20;
SensirionHygrometer sensirionHygro(&sht20, "RH");
SensirionThermometer sensirionThermo(&sht20, "Tamb2");

Pyranometer pyranometer("Irr");

Timer timer(readInterval, uploadInterval);

Anemometer anemometer(12, "WS", 1.25, &timer);
Flowmeter flow(13, "FLOW", 1.25, &timer);

int Sensor::count = 0;
Sensor *sensors[] = {
    &therm1,
    &therm2,
    &therm3,
    &therm4,
    &therm5,
    &therm6,
    &therm7,
    //  &therm8,
    &therm9,
    &therm10,
    &sensirionThermo,
    &sensirionHygro,
    &pyranometer,
    &anemometer,
    &flow};

Logger logger(sensors);

void setup()
{
  Serial.begin(115200);
  printPins();
}

void loop()
{
  logger.run(readInterval, uploadInterval);
}