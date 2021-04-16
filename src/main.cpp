#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MAX31865.h>

// Use software SPI: CS, DI, DO, CLK
// Adafruit_MAX31865 maxe = Adafruit_MAX31865(15, 18, 4, 5); // As marked on board

// use hardware SPI, just pass in the CS pin
// Use print_spi_pins() to find your board defaults
Adafruit_MAX31865 therm1 = Adafruit_MAX31865(4);  // As marked on board
Adafruit_MAX31865 therm2 = Adafruit_MAX31865(5);  // As marked on board
Adafruit_MAX31865 therm3 = Adafruit_MAX31865(13); // As marked on board
Adafruit_MAX31865 therm4 = Adafruit_MAX31865(14); // As marked on board
Adafruit_MAX31865 therm5 = Adafruit_MAX31865(27); // As marked on board
Adafruit_MAX31865 therm6 = Adafruit_MAX31865(26); // As marked on board
Adafruit_MAX31865 therm7 = Adafruit_MAX31865(25); // As marked on board
Adafruit_MAX31865 therm8 = Adafruit_MAX31865(33); // As marked on board
Adafruit_MAX31865 therm9 = Adafruit_MAX31865(32); // As marked on board
// Adafruit_MAX31865 therm2 = Adafruit_MAX31865(4);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF 4300.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL 1000.0

float temp1;
float temp2;
float temp3;
float temp4;
float temp5;
float temp6;
float temp7;
float temp8;
float temp9;

void printSpiPins()
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
  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  printSpiPins();
  therm1.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm2.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm3.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm4.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm5.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm6.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm7.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm8.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm9.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  // therm2.begin(MAX31865_3WIRE); // set to 2WIRE or 4WIRE as necessary
}

void loop()
{

  // Serial.print(therm1.temperature(RNOMINAL, RREF));
  // Serial.print(", ");
  // Serial.print(therm2.temperature(RNOMINAL, RREF));
  // Serial.print(", ");
  // Serial.print(therm3.temperature(RNOMINAL, RREF));
  // Serial.print(", ");
  // Serial.print(therm4.temperature(RNOMINAL, RREF));
  // Serial.print(", ");
  // Serial.print(therm5.temperature(RNOMINAL, RREF));
  // Serial.print(", ");
  // Serial.print(therm6.temperature(RNOMINAL, RREF));
  // Serial.print(", ");
  // Serial.print(therm7.temperature(RNOMINAL, RREF));
  // Serial.print(", ");
  // Serial.print(therm8.temperature(RNOMINAL, RREF));
  // Serial.print(", ");
  // Serial.print(therm9.temperature(RNOMINAL, RREF));
  // Serial.println();
  long start = millis();
  temp1 = therm1.temperature(RNOMINAL, RREF);
  temp2 = therm2.temperature(RNOMINAL, RREF);
  temp3 = therm3.temperature(RNOMINAL, RREF);
  temp4 = therm4.temperature(RNOMINAL, RREF);
  temp5 = therm5.temperature(RNOMINAL, RREF);
  temp6 = therm6.temperature(RNOMINAL, RREF);
  temp7 = therm7.temperature(RNOMINAL, RREF);
  temp8 = therm8.temperature(RNOMINAL, RREF);
  temp9 = therm9.temperature(RNOMINAL, RREF);
  Serial.println(millis() - start);
  delay(1000);
}