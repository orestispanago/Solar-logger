#include <thermometers.h>

#define RREF 4300.0     // Reference resistor, PT100: 430.0, PT1000: 4300.0
#define RNOMINAL 1000.0 // 0 deg C resistance,  PT100: 100.0, PT1000: 1000.0

int thermPins[] = {4, 5, 13, 14, 27, 26, 25, 33, 32}; // CS pins
const int NTHERMS = sizeof(thermPins) / sizeof(thermPins[0]);

Adafruit_MAX31865 *therms[NTHERMS];

float tempValues[NTHERMS];



Thermometers::Thermometers()
{   
    for (int i = 0; i < NTHERMS; i++)
    {
        int pin = thermPins[i];
        therms[i] = new Adafruit_MAX31865(pin);
        therms[i]->begin(MAX31865_4WIRE);
    }
}

void Thermometers::read()
{
    for (int i = 0; i < NTHERMS; i++)
    {
        tempValues[i] = therms[i]->temperature(RNOMINAL, RREF);
    }
}

void Thermometers::print()
{
    Serial.print("[ ");
    for (int i = 0; i < NTHERMS; i++)
    {
        Serial.print(tempValues[i]);
        Serial.print(" ");
    }
    Serial.println(" ]");
}

int Thermometers::getNumber(){
    return NTHERMS;
}

float* Thermometers::getTempValues(){
    return tempValues;
}
