#include "Flowmeter.h"

unsigned long flowPulseCount;

void IRAM_ATTR flowPulseCounter()
{
    flowPulseCount++;
    if (flowPulseCount == 0)
    {
        Serial.println("flowPulseCount reset to 0 due to overflow.");
    }
}

void initFlowmeter(int pin)
{
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), flowPulseCounter, FALLING);
}

Flowmeter::Flowmeter(int pin1, const char label[], float pulsesPerLitre, Timer *timer)
{
    _pin = pin1;
    this->label = label;
    initFlowmeter(_pin);
    _timer = timer;
    _pulsesPerLitre = pulsesPerLitre;
}

float Flowmeter::_frequency()
{
    // Hz = pulseCount / timedelta in seconds
    return flowPulseCount * 1000.0 / (_timer->currentMillis - _timer->lastReadMillis);
}

float Flowmeter::_litresPerSecond()
{
    // Transfer function: L/s = Hz / pulsesPerLitre
    return _frequency() / _pulsesPerLitre;
}

float Flowmeter::_litresPerHour()
{
    return _litresPerSecond() * 3600;
}

void Flowmeter::read()
{
    measurement.sample(_litresPerHour());
    flowPulseCount = 0;
}