### Solar-logger

WiFi-based data logger for solar thermal collectors, developed on an ESP32 board.

### Sensors

| Physical quantity | Sensor           | Interface | Board    |
|-------------------|:----------------:|:---------:|:--------:|
| Temperature       | PT100/PT1000     | SPI       | MAX31865 |
| Irradiance        | Pyranometer      | I2C       | ADS1115  |
| RH                | SHT20            | I2C       | -        |
| Flow              | Pulse flowmeter  | -         | -        |
| Wind speed        | Pulse anemometer | -         | -        |


### Workflow

On each iteration of the main ```loop()```, the ESP32 checks for connection status.

When the specified sampling interval has passed, all sensors are read and the measurement stats ```min, max, mean, stdev``` are calculated and stored in the ```Measurement``` object.

When the upload interval has passed, the ```JSON``` payload is updated with ```mean``` and ```stdev``` values. 

The ```Measurenent``` stats are reset and the payload is published to the MQTT broker.

![flowchart](out/extras/flowchart/flowchart.png)

### Configuration

Set the WiFi network and MQTT broker credentials in ```src/credentials.h```.

Configure the sampling and upload intervals as well as the sensors parameters (pins, labels etc) in the ```src/main.cpp```.

Thats all!

### Structure

To simplify the configuration process and avoid duplicate code, the project has been structured like this:

```mermaid
classDiagram
Sensor *-- Measurement
Sensor <-- Anemometer
Sensor <-- Flowmeter
Sensor <-- Pyranometer
Sensor <-- PT
Sensor <-- SensirionThermometer
Sensor <-- SensirionHygrometer
Anemometer *-- Timer
Flowmeter *-- Timer
SensirionHygrometer *-- ThermoHygrometer
SensirionThermometer *-- ThermoHygrometer

Logger *-- Sensor
Logger *-- Timer
Logger *-- Connection
class Sensor{
    + read() : virtual
    + measurement : Measurement
    + label
    + count
}
class Measurement{
    - _count
    - _current
    - _sum
    - _mean
    - _min
    - _max
    - _sqDiffMean
    - _stdev
    + count()
    + current()
    + sum()
    + mean()
    + min()
    + max()
    + stdev()
    + sample(_current)
    - _reset()
}
class Timer{
    + Timer(readIntervalMillis, uploadIntervalMillis)
    + readInterval
    + uploadInterval
    + currentMillis
    + lastReadMillis
    + lastUploadMillis
}
class Anemometer{
    + Anemometer(pin, label, pulsesPerMetre, timer)
    + read()
    - _pin
    - _timer : Timer
    - _pulsesPerMetre
    - _frequency()
    - _metresPerSecond()
}
class Flowmeter{
    + Flowmeter(pin, label, pulsesPerLitre, timer)
    + read()
    - _pin
    - _pulsesPerLitre
    - Timer _timer
    - _frequency()
    - _litresPerSecond()
    - _litresPerHour()
}
class Pyranometer{
    + Pyranometer(label)
    + read()
    - _ads : Adafruit_ADS1115
    - _init()
}
class PT{
    + PT(rtdType, wires, pin, label)
    + read()
    -_max31865 : Adafruit_MAX31865
    - _rRef
    - _rNominal
    - _wires
    - _begin()
}
class ThermoHygrometer{
    - _sht20 : DFRobot_SHT20
    - _init()
}
class SensirionHygrometer{
    + SensirionHygrometer(thermoHygrometer, label)
    + read()
    - _thermoHygrometer : ThermoHygrometer
}
class SensirionThermometer{
    + SensirionThermometer(thermoHygrometer, label)
    + read()
    - _themoHygrometer : ThermoHygrometer
}
class Connection{
    + Connection()
    + statusOK() : boolean
    + upload(payload)
    + loop()
    - messageSize
    - status
    - waitCount
    - espClient : WiFiClient
    - clientId
}
class Logger{
    + Logger(sensors, timer)
    + run();
    - _sensors : Sensor
    - _timer : Timer
    - _client : WiFiMQTTClient
    - _jsonDoc
    - _payload
    - _update()
    - _readAll()
    - _printPayload()
    - _readAtInterval()
    - _uploadAtInterval()
}

```



### Requirements

An MQTT broker is necessary to receive the payload and a really simple back end to insert the measurements to a database.

This project uses the [Logger-stack](https://github.com/orestispanago/Logger-stack), a dockerized Mosquitto+NodeRed+MySQL+Grafana server stack to receive, store and visualize measurements. 
