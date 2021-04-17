#include <Arduino.h>
#include <thermometers.h>

// Use print_spi_pins() to find your board defaults
// Adafruit_MAX31865 therm1 = Adafruit_MAX31865(4); // As marked on board

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


Thermometers thermos;

void setup()
{
  Serial.begin(115200);
  printPins();
}

void loop()
{
  long start = millis();
  thermos.read();
  thermos.print();
  // float * a = thermos.getTempValues();
  // Serial.println(a[0]);
  Serial.println(millis() - start);
  delay(1000);
}
