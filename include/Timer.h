#ifndef Timer_h
#define Timer_h
#include <Arduino.h>

class Timer
{
public:
    Timer(unsigned long readInterval, unsigned long uploadInterval);
    unsigned long readInterval,
        uploadInterval,
        currentMillis,
        lastReadMillis,
        lastUploadMillis;

private:
    Timer *_timer;
};

#endif