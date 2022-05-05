#include "utils.h"
#include "PT.h"
#include "Pyranometer.h"
#include "SensirionThermometer.h"
#include "Logger.h"
#include "Flowmeter.h"
#include "Anemometer.h"

Timer timer(2000, 10000); // sampling, upload interval in milliseconds

Sensor *sensors[] = {
    new PT(1000, FOUR_WIRE, 0, "Tin"),
    new PT(1000, FOUR_WIRE, 4, "Tout"),
    new PT(1000, FOUR_WIRE, 16, "Tamb"),
    new Pyranometer("Irr"),
    new Anemometer(12, "Wind", 1.25, &timer),
    new Flowmeter(13, "Flow", 1800, &timer),
};

Logger logger(sensors, &timer, len(sensors));

void setup()
{
  Serial.begin(115200);
  // printPins();
}

void loop()
{
  logger.run();
}