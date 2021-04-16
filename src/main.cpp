#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MAX31865.h>

// Use print_spi_pins() to find your board defaults
// Adafruit_MAX31865 therm1 = Adafruit_MAX31865(4); // As marked on board

#define RREF 4300.0     // Reference resistor, PT100: 430.0, PT1000: 4300.0
#define RNOMINAL 1000.0 // 0 deg C resistance,  PT100: 100.0, PT1000: 1000.0

const int NTHERMS = 9;
int thermPins[NTHERMS] = {4, 5, 13, 14, 27, 26, 25, 33, 32}; // CS pins

Adafruit_MAX31865 *therms[NTHERMS];

float tempValues[NTHERMS];

void printPins()
{
  Serial.println();
  Serial.println("======================");
  Serial.println("Hardware SPI GPIO pins");
  Serial.print("MOSI: \t");
  Serial.println(MOSI);
  Serial.print("MISO: \t");
  Serial.println(MISO);
  Serial.print("SCK: \t");
  Serial.println(SCK);
  Serial.print("SS: \t");
  Serial.println(SS);
  Serial.println("======================");
  Serial.println("Default I2C GPIO pins");
  Serial.print("SDA: \t");
  Serial.println(SDA);
  Serial.print("SCL: \t");
  Serial.println(SCL);
  Serial.println();
}

void initTherms()
{
  for (int i = 0; i < NTHERMS; i++)
  {
    int pin = thermPins[i];
    therms[i] = new Adafruit_MAX31865(pin);
    therms[i]->begin(MAX31865_4WIRE);
  }
}

void readTemps()
{
  for (int i = 0; i < NTHERMS; i++)
  {
    tempValues[i] = therms[i]->temperature(RNOMINAL, RREF);
  }
}

void printTemps()
{
  Serial.print("[ ");
  for (int i = 0; i < NTHERMS; i++)
  {
    Serial.print(tempValues[i]);
    Serial.print(" ");
  }
  Serial.println(" ]");
}

void setup()
{
  Serial.begin(115200);
  printPins();
  initTherms();
}

void loop()
{
  long start = millis();
  readTemps();
  printTemps();

  Serial.println(millis() - start);
  delay(1000);
}
