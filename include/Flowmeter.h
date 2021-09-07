#ifndef Flowmeter_h
#define Flowmeter_h

#include "Sensor.h"

class Flowmeter : public Sensor
{
public:
    Flowmeter(int pin1, const char label[]);
    void read();

private:
    int _pin;
};
#endif