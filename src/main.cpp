#include <Arduino.h>
#include "WiFiMQTTClient.h"
#include "utils.h"
#include "RTD.h"
#include "Pyranometer.h"
// #include "SensirionThermometer.h"
// #include "SensirionHygrometer.h"
// #include "Row.h"
// #include "MeasurementService.h"

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

// ThermoHygrometer sht20;
// SensirionHygrometer sensirionHygro(&sht20);
// SensirionThermometer sensirionThermo(&sht20);

Pyranometer pyranometer("Irr");

Sensor *sensors[] = {&therm1,
                     &therm2,
                     &pyranometer};

int numSensors = sizeof(sensors) / sizeof(sensors[0]);

void readAll()
{
  for (int i = 0; i < numSensors; i++)
  {
    sensors[i]->read();
  }
}
void printMean()
{
  for (int i = 0; i < numSensors; i++)
  {
    Serial.print(sensors[i]->label);
    Serial.print(sensors[i]->quant.mean());
  }
  Serial.println();
}

// Quantity quantities[] = {
//     Quantity("Tin", &therm1),
//     Quantity("Tout", &therm2),
//     Quantity("Tamb", &therm3),
//     Quantity("Tafb", &therm4),
//     Quantity("Tafb", &therm5),
//     Quantity("Taft", &therm6),
//     Quantity("Tabm", &therm7),
//     Quantity("Tout", &therm8),
//     Quantity("Tamb2", &sensirionThermo),
//     Quantity("RH", &sensirionHygro),
//     Quantity("Irr", &pyranometer)};

WiFiMQTTClient client;

// int numQuantities = sizeof(quantities) / sizeof(quantities[0]);
// Row row(quantities, numQuantities);

// MeasurementService ms(&row, &client);

void setup()
{
  Serial.begin(115200);
  printPins();
}

void loop()
{
  if (client.connected())
  {
    // ms.readAtInterval(readInterval);
    // ms.uploadAtInterval(uploadInterval);
    // sensors[0]->read();
    // Serial.print(sensors[0]->label);
    // sensors[0]->quant.print();
    readAll();
    printMean();
    delay(3000);
    client.loop();
  }
}