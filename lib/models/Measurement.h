#ifndef Measurement_h
#define Measurement_h

class Measurement
{
public:
    Measurement();
    unsigned long count();
    float current();
    float sum();
    float mean();
    float min();
    float max();
    float stdev();
    void sample(float current);
    void print();

private:
    unsigned long _count;
    float _current;
    float _sum;
    float _mean;
    float _min;
    float _max;
    float _sqDiffMean;
    float _stdev;
    void _reset();
};

#endif