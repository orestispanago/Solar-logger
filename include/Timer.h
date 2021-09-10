#ifndef Timer_h
#define Timer_h
#include <Arduino.h>

class Timer
{
public:
    Timer(unsigned long readIntervalMillis, unsigned long uploadIntervalMillis);
    unsigned long readInterval,
        uploadInterval,
        currentMillis,
        lastReadMillis,
        lastUploadMillis;
};

#endif