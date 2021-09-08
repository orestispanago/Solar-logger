#ifndef Flowmeter_h
#define Flowmeter_h

#include "Sensor.h"
#include "Timer.h"

class Flowmeter : public Sensor
{
public:
    Flowmeter(int pin1, const char label[], float calibrationFactor, Timer *timer);
    void read();

private:
    int _pin;
    float _calibrationFactor;
    Timer *_timer;
    float _flow;
};
#endif