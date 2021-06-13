#include <Arduino.h>
#include "Connection.h"
#include "utils.h"
#include "RTD.h"
#include "Pyranometer.h"
#include "ThermoHygrometer.h"
#include "Quantity.h"

unsigned long readInterval = 2000;
unsigned long uploadInterval = 10000;

unsigned long currentMillis, lastReadMillis, lastUploadMillis;

RTD therm1 = RTD(PT1000, FOUR_WIRE, 4);
RTD therm2 = RTD(PT1000, FOUR_WIRE, 5);
RTD therm3 = RTD(PT1000, FOUR_WIRE, 13);
RTD therm4 = RTD(PT1000, FOUR_WIRE, 14);
RTD therm5 = RTD(PT1000, FOUR_WIRE, 27);
RTD therm6 = RTD(PT1000, FOUR_WIRE, 26);
RTD therm7 = RTD(PT1000, FOUR_WIRE, 25);
RTD therm8 = RTD(PT1000, FOUR_WIRE, 33);

ThermoHygrometer sht20;
Pyranometer pyranometer;

// Quantity rh = Quantity("RH", &sht20);

Quantity quantities[] = {
    Quantity("Tin", &therm1),
    Quantity("Tout", &therm2),
    Quantity("Tamb", &therm3),
    Quantity("Tafb", &therm4),
    Quantity("Tafb", &therm5),
    Quantity("Taft", &therm6),
    Quantity("Tabm", &therm7),
    Quantity("Tout", &therm8),
    Quantity("Irr", &pyranometer)};

int numQuantities = sizeof(quantities) / sizeof(quantities[0]);

void readAll()
{
  for (int i = 0; i < numQuantities; i++)
  {
    quantities[i].sample();
  }
}

void updatePayload()
{
  jsonDoc["count"] = quantities[0].count();
  for (int i = 0; i < numQuantities; i++)
  {
    jsonDoc[quantities[i].label] = quantities[i].mean();
  }
  jsonDoc["heapUsage"] = getHeapUsage();
}

void setup()
{
  Serial.begin(115200);
  printPins();
  WiFi.mode(WIFI_STA); // config WiFi as client
}

void loop()
{
  if (statusOK())
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
      upload();
    }
    check();
  }
}