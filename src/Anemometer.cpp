#include "Anemometer.h"

unsigned long windPulseCount;

void IRAM_ATTR windPulseCounter()
{
    windPulseCount++;
    if (windPulseCount == 0)
    {
        Serial.println("windPulseCount reset to 0 due to overflow.");
    }
}

void initAnemometer(int pin)
{
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), windPulseCounter, FALLING);
}

Anemometer::Anemometer(int pin1, const char label[], float calibrationFactor, Timer *timer)
{
    _pin = pin1;
    this->label = label;
    initAnemometer(_pin);
    _timer = timer;
    _calibrationFactor = calibrationFactor;
}

void Anemometer::read()
{
    _windSpeed = windPulseCount * _calibrationFactor / ((_timer->currentMillis - _timer->lastReadMillis) / 1000);
    measurement.sample(_windSpeed);
    windPulseCount = 0;
}