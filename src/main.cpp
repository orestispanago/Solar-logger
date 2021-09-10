#include <Arduino.h>
#include "utils.h"
#include "PT.h"
#include "Pyranometer.h"
#include "SensirionThermometer.h"
#include "SensirionHygrometer.h"
#include "Logger.h"
#include "Flowmeter.h"
#include "Anemometer.h"

Timer timer(2000, 10000); // sampling, upload interval in milliseconds

ThermoHygrometer sht20;

Sensor *sensors[] = {
    new PT(PT1000, FOUR_WIRE, 17, "ABD"),
    new PT(PT1000, FOUR_WIRE, 16, "ABU"),
    new PT(PT1000, FOUR_WIRE, 4, "AFD"),
    new PT(PT1000, FOUR_WIRE, 0, "AFMD"),
    new PT(PT1000, FOUR_WIRE, 32, "AFMU"),
    new PT(PT1000, FOUR_WIRE, 33, "AFU"),
    new PT(PT1000, FOUR_WIRE, 25, "IM"),
    new PT(PT100, FOUR_WIRE, 27, "OUT"),
    new PT(PT100, FOUR_WIRE, 14, "IN"),
    new SensirionThermometer(&sht20, "Tamb2"),
    new SensirionHygrometer(&sht20, "RH"),
    new Pyranometer("Irr"),
    new Anemometer(12, "WS", 1.25, &timer),
    new Flowmeter(13, "FLOW", 1800, &timer),
};

Logger logger(sensors, &timer, len(sensors));

void setup()
{
  Serial.begin(115200);
  printPins();
}

void loop()
{
  logger.run();
}