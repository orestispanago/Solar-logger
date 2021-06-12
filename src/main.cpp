#include <Arduino.h>
#include "Connection.h"
#include "utils.h"
#include "Sensors.h"

unsigned long readInterval = 2000;
unsigned long uploadInterval = 10000;

unsigned long currentMillis, lastReadMillis, lastUploadMillis;

void setup()
{
  Serial.begin(115200);
  printPins();
  WiFi.mode(WIFI_STA); // config WiFi as client
}

void readAll()
{
  t1.sample(therm1.temperature());
  t2.sample(therm2.temperature());
  t3.sample(therm3.temperature());
  t4.sample(therm4.temperature());
  t5.sample(therm5.temperature());
  t6.sample(therm6.temperature());
  t7.sample(therm7.temperature());
  t8.sample(therm8.temperature());
  t9.sample(therm9.temperature());
  t10.sample(sht20.temperature());
  h1.sample(sht20.humidity());
  irr.sample(pyranometer.voltage());
}

void updatePayload()
{
  jsonDoc["count"] = t1.count();
  jsonDoc["t1"] = t1.mean();
  jsonDoc["t2"] = t2.mean();
  jsonDoc["t3"] = t3.mean();
  jsonDoc["t4"] = t4.mean();
  jsonDoc["t5"] = t5.mean();
  jsonDoc["t6"] = t6.mean();
  jsonDoc["t7"] = t7.mean();
  jsonDoc["t8"] = t8.mean();
  jsonDoc["t9"] = t9.mean();
  jsonDoc["t10"] = t10.mean();
  jsonDoc["h1"] = h1.mean();
  jsonDoc["irr"] = irr.mean();
  jsonDoc["freeHeap"] = ESP.getFreeHeap();
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
      resetMeasurements();
      upload();
    }
    check();
  }
}