#include <Arduino.h>

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
