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

Flowmeter::Flowmeter(int pin1, const char label[])
{
    _pin = pin1;
    this->label = label;
    initFlowmeter(_pin);
}

void Flowmeter::read()
{
    quant.sample(flowPulseCount * 1.2);
}