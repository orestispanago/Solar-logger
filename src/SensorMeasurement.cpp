#include "SensorMeasurement.h"

SensorMeasurement::SensorMeasurement(String name, Sensor *sensor, Measurement *measurement)
{
    name = name;
    _sensor = sensor;
    _measurement = measurement;
}
void SensorMeasurement::sample()
{
    _measurement->sample(_sensor->read());
    // _sensor->read();
}
void SensorMeasurement::reset()
{
    _measurement->reset();
}
float SensorMeasurement::value()
{
    return _measurement->mean();
}