#include "Pyranometer.h"

Pyranometer::Pyranometer(const char label[], float sensitivity)
{
    this->label = label;
    Adafruit_ADS1115 _ads(0x48);
    _ads.begin();
    _sensitivity = sensitivity;
}
void Pyranometer::read()
{
    _adc0 = _ads.readADC_SingleEnded(_adsPin);
    measurement.sample(_adc0 * 0.1875 / _sensitivity); // millivolts, reference_voltage/possible_values: 6.144/2^(16-1)=0.1875
    // divide by _sensitivity V/(W.m-2) to get W.m-2
}
