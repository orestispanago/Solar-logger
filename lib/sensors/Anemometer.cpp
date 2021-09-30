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

Anemometer::Anemometer(int pin1, const char label[], float pulsesPerMetre, Timer *timer)
{
    _pin = pin1;
    this->label = label;
    initAnemometer(_pin);
    _timer = timer;
    _pulsesPerMetre = pulsesPerMetre;
}

float Anemometer::_frequency()
{
    // Hz = pulseCount / timedelta in seconds
    return windPulseCount * 1000 / (_timer->currentMillis - _timer->lastReadMillis);
}

float Anemometer::_metresPerSecond()
{
    // Transfer function: m/s = Hz / pulsesPerMetre
    return _frequency() * _pulsesPerMetre;
}

void Anemometer::read()
{
    measurement.sample(_metresPerSecond());
    windPulseCount = 0;
}