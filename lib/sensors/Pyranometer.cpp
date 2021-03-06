#include "Pyranometer.h"

Pyranometer::Pyranometer(const char label[])
{
    this->label = label;
    Adafruit_ADS1115 _ads(0x49);
    uint _adsPin = 0;
}
void Pyranometer::read()
{
    int16_t adc0;
    adc0 = _ads.readADC_SingleEnded(_adsPin);
    measurement.sample(adc0 * 0.1875); // millivolts, reference_voltage/possible_values: 6.144/2^(16-1)=0.1875
}
void Pyranometer::_init()
{
    _ads.begin();
}