#ifndef MeasurementService_h
#define MeasurementService_h

#include "Row.h"
#include "WiFiMQTTClient.h"

class MeasurementService
{
public:
    MeasurementService(Row *row, WiFiMQTTClient *client);
    void readAtInterval(unsigned long readIinterval);
    // void uploadAtInterval(unsigned long uploadInterval);

private:
    Row *_row;
    WiFiMQTTClient *_client;
    unsigned long _currentMillis;
    unsigned long _lastReadMillis;
    unsigned long _lastUploadMillis;
};
#endif