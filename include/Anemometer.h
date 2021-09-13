#ifndef Anemometer_h
#define Anemometer_h

#include "Sensor.h"
#include "Timer.h"

class Anemometer : public Sensor
{
public:
    Anemometer(int pin1, const char label[], float pulsesPerMetre, Timer *timer);
    void read();

private:
    int _pin;
    Timer *_timer;  
    float _pulsesPerMetre;
    float _frequency();
    float _metresPerSecond();
};
#endif