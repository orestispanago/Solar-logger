#include <Arduino.h>
#include "WiFiMQTTClient.h"
#include "utils.h"
#include "RTD.h"
#include "Pyranometer.h"
#include "SensirionThermometer.h"
#include "SensirionHygrometer.h"
#include "Quantity.h"
#include "Row.h"

unsigned long readInterval = 2000;
unsigned long uploadInterval = 6000;

unsigned long currentMillis, lastReadMillis, lastUploadMillis;

RTD therm1(PT1000, FOUR_WIRE, 17);
RTD therm2(PT1000, FOUR_WIRE, 16);
RTD therm3(PT1000, FOUR_WIRE, 4);
RTD therm4(PT1000, FOUR_WIRE, 0);

RTD therm5(PT1000, FOUR_WIRE, 32);
RTD therm6(PT1000, FOUR_WIRE, 33);
RTD therm7(PT1000, FOUR_WIRE, 25);
RTD therm8(PT1000, FOUR_WIRE, 26);
RTD therm9(PT1000, FOUR_WIRE, 27);
RTD therm10(PT1000, FOUR_WIRE, 14);

ThermoHygrometer sht20;
SensirionHygrometer sensirionHygro(&sht20);
SensirionThermometer sensirionThermo(&sht20);

Pyranometer pyranometer;

Quantity quantities[] = {
    Quantity("Tin", &therm1),
    Quantity("Tout", &therm2),
    Quantity("Tamb", &therm3),
    Quantity("Tafb", &therm4),
    Quantity("Tafb", &therm5),
    Quantity("Taft", &therm6),
    Quantity("Tabm", &therm7),
    Quantity("Tout", &therm8),
    Quantity("Tamb2", &sensirionThermo),
    Quantity("RH", &sensirionHygro),
    Quantity("Irr", &pyranometer)};

WiFiMQTTClient client;

int numQuantities = sizeof(quantities) / sizeof(quantities[0]);
Row row(quantities, numQuantities);

void setup()
{
  Serial.begin(115200);
  printPins();
}

void loop()
{
  if (client.connected())
  {
    currentMillis = millis();
    if (currentMillis - lastReadMillis >= readInterval)
    {
      lastReadMillis = currentMillis;
      row.readAll();
    }
    currentMillis = millis();
    if (currentMillis - lastUploadMillis >= uploadInterval)
    {
      lastUploadMillis = currentMillis;
      row.update();
      row.print();
      client.upload(row);
    }
    client.loop();
  }
}