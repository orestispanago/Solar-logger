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

Flowmeter::Flowmeter(int pin1, const char label[], float calibrationFactor, Timer *timer)
{
    _pin = pin1;
    this->label = label;
    initFlowmeter(_pin);
    _timer = timer;
    _calibrationFactor = calibrationFactor;
}

void Flowmeter::read()
{
    flow = flowPulseCount * _calibrationFactor / ((_timer->currentMillis - _timer->lastReadMillis) / 1000);
    quant.sample(flow);
    _timer->lastReadMillis = _timer->currentMillis;
    flowPulseCount = 0;
}