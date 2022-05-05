#include "Pyranometer.h"

Pyranometer::Pyranometer(const char label[])
{
    this->label = label;
    Adafruit_ADS1115 _ads(0x48);
    _ads.begin();
}
void Pyranometer::read()
{
    _adc0 = _ads.readADC_SingleEnded(_adsPin);
    measurement.sample(_adc0 * 0.1875); // millivolts, reference_voltage/possible_values: 6.144/2^(16-1)=0.1875
}
