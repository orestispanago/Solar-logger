#ifndef Measurement_h
#define Measurement_h

#include "Arduino.h"

class Measurement
{
public:
    Measurement();
    long getCount();
    float getCurrent();
    float getTotal();
    float average();
    void sample(float newVal);

private:
    long count;
    float current;
    float total;
    float _average;
};

#endif