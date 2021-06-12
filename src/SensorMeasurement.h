#ifndef SensorMeasurement_h
#define SensorMeasurement_h

#include "Sensor.h"
#include "Measurement.h"

class SensorMeasurement
{
public:
    SensorMeasurement(String name, Sensor *sensor, Measurement *measurement);
    char *name;
    void sample();
    void reset();
    float value();

private:
    Measurement *_measurement;
    Sensor *_sensor;
};

#endif