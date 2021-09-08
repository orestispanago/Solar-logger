#ifndef Anemometer_h
#define Anemometer_h

#include "Sensor.h"
#include "Timer.h"

class Anemometer : public Sensor
{
public:
    Anemometer(int pin1, const char label[], float calibrationFactor, Timer *timer);
    void read();
    float windSpeed;

private:
    int _pin;
    float _calibrationFactor;
    Timer *_timer;
};
#endif