#include "Timer.h"

Timer::Timer(unsigned long readInterval, unsigned long uploadInterval)
{
    readInterval = readInterval;
    uploadInterval = uploadInterval;
    lastUploadMillis = millis();
}