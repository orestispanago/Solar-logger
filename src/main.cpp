#include <Arduino.h>
#include "utils.h"
#include "PT.h"
#include "Pyranometer.h"
#include "SensirionThermometer.h"
#include "SensirionHygrometer.h"
#include "LoggerService.h"
#include "Flowmeter.h"
#include "Anemometer.h"

Timer timer(2000, 10000); // sampling, upload interval in milliseconds

ThermoHygrometer sht20;

Sensor *sensors[] = {
    new PT(1000, FOUR_WIRE, 17, "Tabd"),
    new PT(1000, FOUR_WIRE, 16, "Tabu"),
    new PT(1000, FOUR_WIRE, 4, "Tafd"),
    new PT(1000, FOUR_WIRE, 0, "Tafmd"),
    new PT(1000, FOUR_WIRE, 32, "Tafmu"),
    new PT(1000, FOUR_WIRE, 33, "Tafu"),
    new PT(1000, FOUR_WIRE, 25, "Tim"),
    new PT(1000, FOUR_WIRE, 26, "Tenv"),
    new PT(100, FOUR_WIRE, 27, "Tout"),
    new PT(100, FOUR_WIRE, 14, "Tin"),
    new SensirionThermometer(&sht20, "Tenv2"),
    new SensirionHygrometer(&sht20, "RH"),
    new Pyranometer("Irr"),
    new Anemometer(12, "Wind", 1.25, &timer),
    new Flowmeter(13, "Flow", 1800, &timer),
};

LoggerService loggerService(sensors, &timer, len(sensors));

void setup()
{
  Serial.begin(115200);
  printPins();
}

void loop()
{
  loggerService.run();
}