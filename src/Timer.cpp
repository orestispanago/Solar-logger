#include "Timer.h"

Timer::Timer(unsigned long readIntervalMillis, unsigned long uploadIntervalMillis)
{
    readInterval = readIntervalMillis;
    uploadInterval = uploadIntervalMillis;
    // lastUploadMillis = millis();
    // lastReadMillis = millis();
}