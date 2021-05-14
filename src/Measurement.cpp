#include "Arduino.h"
#include "Measurement.h"

Measurement::Measurement()
{
}

float Measurement::getCurrent()
{
    return current;
}

float Measurement::getTotal()
{
    return total;
}

float Measurement::average()
{
    total = 0.0;
    count = 0.0;
    return _average;
}

long Measurement::getCount()
{
    return count;
}

void Measurement::sample(float newVal)
{
    count++;
    current = newVal;
    total = total + current;
    _average = (total / count);
}
