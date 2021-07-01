#include <Arduino.h>
#include "WiFiMQTTClient.h"
#include "utils.h"
#include "RTD.h"
#include "Pyranometer.h"
#include "SensirionThermometer.h"
#include "SensirionHygrometer.h"
#include "Quantity.h"

unsigned long readInterval = 2000;
unsigned long uploadInterval = 10000;

unsigned long currentMillis, lastReadMillis, lastUploadMillis;

RTD therm1 = RTD(PT1000, FOUR_WIRE, 17);
RTD therm2 = RTD(PT1000, FOUR_WIRE, 16);
RTD therm3 = RTD(PT1000, FOUR_WIRE, 4);
RTD therm4 = RTD(PT1000, FOUR_WIRE, 0);

RTD therm5 = RTD(PT1000, FOUR_WIRE, 32);
RTD therm6 = RTD(PT1000, FOUR_WIRE, 33);
RTD therm7 = RTD(PT1000, FOUR_WIRE, 25);
RTD therm8 = RTD(PT1000, FOUR_WIRE, 26);
RTD therm9 = RTD(PT1000, FOUR_WIRE, 27);
RTD therm10 = RTD(PT1000, FOUR_WIRE, 14);

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

int numQuantities = sizeof(quantities) / sizeof(quantities[0]);

WiFiMQTTClient client;

void readAll()
{
  for (int i = 0; i < numQuantities; i++)
  {
    quantities[i].sample();
  }
}

void updatePayload()
{
  client.jsonDoc["count"] = quantities[0].count();
  for (int i = 0; i < numQuantities; i++)
  {
    client.jsonDoc[quantities[i].label] = quantities[i].mean();
  }
  client.jsonDoc["heapUsage"] = getHeapUsage();
}

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
      readAll();
    }
    currentMillis = millis();
    if (currentMillis - lastUploadMillis >= uploadInterval)
    {
      lastUploadMillis = currentMillis;
      updatePayload();
      client.upload();
    }
    client.loop();
  }
}