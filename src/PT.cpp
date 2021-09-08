#include "PT.h"

PT::PT(PTType ptType, numWires wires, int pin, const char label[])
{
    this->label = label;
    _max31865 = new Adafruit_MAX31865(pin);
    _wires = wires;
    switch (ptType)
    {
    case PT100:
        _rRef = 430.0;
        _rNominal = 100.0;
        break;
    case PT1000:
        _rRef = 4300.0;
        _rNominal = 1000.0;
        break;
    }
    _begin();
}

void PT::_begin()
{
    switch (_wires)
    {
    case TWO_WIRE:
        _max31865->begin(MAX31865_2WIRE);
        break;
    case THREE_WIRE:
        _max31865->begin(MAX31865_3WIRE);
        break;
    case FOUR_WIRE:
        _max31865->begin(MAX31865_4WIRE);
        break;
    }
}
void PT::read()
{
    quant.sample(_max31865->temperature(_rNominal, _rRef));
}