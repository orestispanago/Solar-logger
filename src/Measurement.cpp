#include "Arduino.h"
#include "Measurement.h"

Measurement::Measurement()
{
    _min = 999.99;
    _max = -999.99;
}

float Measurement::current()
{
    return _current;
}

float Measurement::sum()
{
    return _sum;
}

unsigned long Measurement::count()
{
    return _count;
}

float Measurement::mean()
{
    return _mean;
}

float Measurement::min()
{
    return _min;
}

float Measurement::max()
{
    return _max;
}

float Measurement::stdev()
{
    return _stdev;
}


void Measurement::reset()
{
    _sum = 0.0;
    _count = 0.0;
    _min = 999.99;
    _max = -999.99;
    _sqDiffMean = 0;
}

void Measurement::sample(float newVal)
{
    _count++;
    _current = newVal;
    _sum = _sum + _current;
    _mean = (_sum / _count);
    if (newVal < _min)
    {
        _min = newVal;
    }
    if (newVal > _max)
    {
        _max = newVal;
    }
    _sqDiffMean += sq(newVal - _mean);
    _stdev = sqrt(_sqDiffMean / _count);
}

void Measurement::print()
{
    Serial.print("count: ");
    Serial.print(_count);
    Serial.print(", current: ");
    Serial.print(_current);
    Serial.print(", sum: ");
    Serial.print(_sum);
    Serial.print(", mean: ");
    Serial.print(_mean);
    Serial.print(", min: ");
    Serial.print(_min);
    Serial.print(", max: ");
    Serial.print(_max);
    Serial.print(", std: ");
    Serial.println(_stdev);
}