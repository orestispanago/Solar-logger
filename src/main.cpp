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
    new PT(1000, FOUR_WIRE, 17, "ABD"),
    new PT(1000, FOUR_WIRE, 16, "ABU"),
    new PT(1000, FOUR_WIRE, 4, "AFD"),
    new PT(1000, FOUR_WIRE, 0, "SOUT"),
    new PT(1000, FOUR_WIRE, 32, "SIN"),
    new PT(1000, FOUR_WIRE, 33, "AFU"),
    new PT(1000, FOUR_WIRE, 25, "IM"),
    new PT(100, FOUR_WIRE, 27, "OUT"),
    new PT(100, FOUR_WIRE, 14, "IN"),
    new SensirionThermometer(&sht20, "Tamb2"),
    new SensirionHygrometer(&sht20, "RH"),
    new Pyranometer("Irr"),
    new Anemometer(12, "WS", 1.25, &timer),
    new Flowmeter(13, "FLOW", 1800, &timer),
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