#include <Arduino.h>
#include "utils.h"
#include "RTD.h"
#include "Pyranometer.h"
#include "SensirionThermometer.h"
#include "SensirionHygrometer.h"
#include "Logger.h"

unsigned long readInterval = 2000;
unsigned long uploadInterval = 6000;

RTD therm1(PT1000, FOUR_WIRE, 17, "Tinput");
RTD therm2(PT1000, FOUR_WIRE, 16, "Toutput");
// RTD therm3(PT1000, FOUR_WIRE, 4);
// RTD therm4(PT1000, FOUR_WIRE, 0);

// RTD therm5(PT1000, FOUR_WIRE, 32);
// RTD therm6(PT1000, FOUR_WIRE, 33);
// RTD therm7(PT1000, FOUR_WIRE, 25);
// RTD therm8(PT1000, FOUR_WIRE, 26);
// RTD therm9(PT1000, FOUR_WIRE, 27);
// RTD therm10(PT1000, FOUR_WIRE, 14);

ThermoHygrometer sht20;
SensirionHygrometer sensirionHygro(&sht20, "RH");
SensirionThermometer sensirionThermo(&sht20, "Tamb2");

Pyranometer pyranometer("Irr");

int Sensor::count = 0;
Sensor *sensors[] = {&therm1,
                     &therm2,
                     &sensirionThermo,
                     &sensirionHygro,
                     &pyranometer};

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