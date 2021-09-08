#include <Arduino.h>
#include "utils.h"
#include "PT.h"
#include "Pyranometer.h"
#include "SensirionThermometer.h"
#include "SensirionHygrometer.h"
#include "Logger.h"
#include "Flowmeter.h"
#include "Anemometer.h"

unsigned long readInterval = 2000;
unsigned long uploadInterval = 10000;

PT therm1(PT1000, FOUR_WIRE, 17, "ABD");
PT therm2(PT1000, FOUR_WIRE, 16, "ABU");
PT therm3(PT1000, FOUR_WIRE, 4, "AFD");
PT therm4(PT1000, FOUR_WIRE, 0, "AFMD");

PT therm5(PT1000, FOUR_WIRE, 32, "AFMU");
PT therm6(PT1000, FOUR_WIRE, 33, "AFU");
PT therm7(PT1000, FOUR_WIRE, 25, "IM");
// // PT therm8(PT1000, FOUR_WIRE, 26);
PT therm9(PT100, FOUR_WIRE, 27, "OUT");
PT therm10(PT100, FOUR_WIRE, 14, "IN");

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

Logger logger(sensors, &timer);

void setup()
{
  Serial.begin(115200);
  printPins();
}

void loop()
{
  logger.run();
}