#include "Sensor.h"

Sensor::Sensor()
{
    count++;
}
void Sensor::read()
{
    Serial.println("Called read from Sensor (parent class)");
}