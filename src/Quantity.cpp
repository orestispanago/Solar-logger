#include "Arduino.h"
#include "Quantity.h"

Quantity::Quantity(const char name[], Sensor *sensor)
{
    label = name;
    _sensor = sensor;
    _min = 999.99;
    _max = -999.99;
}

float Quantity::current()
{
    return _current;
}

float Quantity::sum()
{
    return _sum;
}

unsigned long Quantity::count()
{
    return _count;
}

float Quantity::mean()
{
    reset();
    return _mean;
}

float Quantity::min()
{
    return _min;
}

float Quantity::max()
{
    return _max;
}

float Quantity::stdev()
{
    return _stdev;
}

void Quantity::reset()
{
    _sum = 0.0;
    _count = 0.0;
    _min = 999.99;
    _max = -999.99;
    _sqDiffMean = 0;
}

void Quantity::sample()
{
    _count++;
    _current = _sensor->read();
    _sum = _sum + _current;
    _mean = (_sum / _count);
    if (_current < _min)
    {
        _min = _current;
    }
    if (_current > _max)
    {
        _max = _current;
    }
    _sqDiffMean += sq(_current - _mean);
    _stdev = sqrt(_sqDiffMean / _count);
}

void Quantity::print()
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