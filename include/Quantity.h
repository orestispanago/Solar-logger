#ifndef Quantity_h
#define Quantity_h

// #include "Sensor.h"

class Quantity
{
public:
    Quantity();
    unsigned long count();
    float current();
    float sum();
    float mean();
    float min();
    float max();
    float stdev();
    void sample(float current);
    void print();
    void reset();
    // const char *label;

private:
    // Sensor *_sensor;
    unsigned long _count;
    float _current;
    float _sum;
    float _mean;
    float _min;
    float _max;
    float _sqDiffMean;
    float _stdev;
};

#endif