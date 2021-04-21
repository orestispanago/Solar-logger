#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MAX31865.h>
#include "DFRobot_SHT20.h"
#include <Adafruit_ADS1015.h>
#include <WiFi.h>
#include <MQTTClient.h> // MQTT Client from Joël Gaehwiler https://github.com/256dpi/arduino-mqtt   keepalive manually to 15s
#include <Measurement.h>

const char* WiFi_SSID = "YourWiFiSSID";           // change according your setup : SSID and password for the WiFi network
const char* WiFi_PW = "YourWiFiPassword";         //    "
const char* mqtt_broker = "YourMQTTBrokerIP";     // change according your setup : IP Adress or FQDN of your MQTT broker
const char* mqtt_user = "YourMQTTBrokerUsername"; // change according your setup : username and password for authenticated broker access
const char* mqtt_pw = "YourMQTTBrokerPassword";   //    "
const char* input_topic = "YourTopic";            // change according your setup : MQTT topic for messages from device to broker

unsigned long readInterval = 2000;
unsigned long uploadInterval = 10000;

unsigned long lastReadMillis;
unsigned long lastUploadMillis;

String clientId;

unsigned long waitCount;
uint8_t conn_stat;
// Connection status for WiFi and MQTT:
//
// status |   WiFi   |    MQTT
// -------+----------+------------
//      0 |   down   |    down
//      1 | starting |    down
//      2 |    up    |    down
//      3 |    up    |  starting
//      4 |    up    | finalising
//      5 |    up    |     up

WiFiClient espClient;       // TCP client object, uses SSL/TLS
MQTTClient mqttClient(512); // MQTT client object with a buffer size of 512 (depends on your message size)

Adafruit_MAX31865 therm1 = Adafruit_MAX31865(4); // As marked on board
Adafruit_MAX31865 therm2 = Adafruit_MAX31865(5);
Adafruit_MAX31865 therm3 = Adafruit_MAX31865(13);
Adafruit_MAX31865 therm4 = Adafruit_MAX31865(14);
Adafruit_MAX31865 therm5 = Adafruit_MAX31865(27);
Adafruit_MAX31865 therm6 = Adafruit_MAX31865(26);
Adafruit_MAX31865 therm7 = Adafruit_MAX31865(25);
Adafruit_MAX31865 therm8 = Adafruit_MAX31865(33);
Adafruit_MAX31865 therm9 = Adafruit_MAX31865(32);

#define RREF 4300.0     // Reference resistor, PT100: 430.0, PT1000: 4300.0
#define RNOMINAL 1000.0 // 0 deg C resistance,  PT100: 100.0, PT1000: 1000.0

DFRobot_SHT20 sht20;

Adafruit_ADS1115 ads(0x49);

Measurement t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, h1, irr;

void printPins()
{
  Serial.println();
  Serial.println("======================");
  Serial.println("Hardware SPI GPIO pins");
  Serial.print("MOSI: \t");
  Serial.println(MOSI);
  Serial.print("MISO: \t");
  Serial.println(MISO);
  Serial.print("SCK: \t");
  Serial.println(SCK);
  Serial.print("SS: \t");
  Serial.println(SS);
  Serial.println("======================");
  Serial.println("Default I2C GPIO pins");
  Serial.print("SDA: \t");
  Serial.println(SDA);
  Serial.print("SCL: \t");
  Serial.println(SCL);
  Serial.println();
}

boolean connected()
{
  if ((WiFi.status() != WL_CONNECTED) && (conn_stat != 1))
  {
    conn_stat = 0;
  }
  if ((WiFi.status() == WL_CONNECTED) && !mqttClient.connected() && (conn_stat != 3))
  {
    conn_stat = 2;
  }
  if ((WiFi.status() == WL_CONNECTED) && mqttClient.connected() && (conn_stat != 5))
  {
    conn_stat = 4;
  }
  switch (conn_stat)
  {
  case 0: // MQTT and WiFi down: start WiFi
    Serial.println("MQTT and WiFi down: start WiFi");
    WiFi.begin(WiFi_SSID, WiFi_PW);
    conn_stat = 1;
    break;
  case 1: // WiFi starting, do nothing here
    Serial.println("WiFi starting, wait : " + String(waitCount));
    waitCount++;
    break;
  case 2: // WiFi up, MQTT down: start MQTT
    Serial.println("WiFi up, MQTT down: start MQTT");
    mqttClient.begin(mqtt_broker, 1883, espClient);          //   config MQTT Server, use port 8883 for secure connection
    clientId = "ESP32Client-" + String(random(0xffff), HEX); // Create a random client ID
    mqttClient.connect(clientId.c_str(), mqtt_user, mqtt_pw);
    conn_stat = 3;
    waitCount = 0;
    break;
  case 3: // WiFi up, MQTT starting, do nothing here
    Serial.println("WiFi up, MQTT starting, wait : " + String(waitCount));
    mqttClient.connect(clientId.c_str(), mqtt_user, mqtt_pw);
    waitCount++;
    break;
  case 4: // WiFi up, MQTT up: finish MQTT configuration
    Serial.println("WiFi up, MQTT up: finish MQTT configuration");
    mqttClient.publish(input_topic, "{\"Status\":\"up and running!\"}");
    conn_stat = 5;
    break;
  }
  return conn_stat == 5;
}

float readVoltage(uint adsPin)
{
  int16_t adc0;
  adc0 = ads.readADC_SingleEnded(adsPin);
  return adc0 * 0.1875; // millivolts, reference_voltage/possible_values: 6.144/2^(16-1)=0.1875
}

void setup()
{
  Serial.begin(115200);
  printPins();
  WiFi.mode(WIFI_STA);          // config WiFi as client
  therm1.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm2.begin(MAX31865_4WIRE);
  therm3.begin(MAX31865_4WIRE);
  therm4.begin(MAX31865_4WIRE);
  therm5.begin(MAX31865_4WIRE);
  therm6.begin(MAX31865_4WIRE);
  therm7.begin(MAX31865_4WIRE);
  therm8.begin(MAX31865_4WIRE);
  therm9.begin(MAX31865_4WIRE);
  sht20.initSHT20();
  delay(100);
  sht20.checkSHT20();
  ads.begin();
}

void loop()
{
  if (connected())
  {
    if (millis() - lastReadMillis >= readInterval)
    {
      t1.update(therm1.temperature(RNOMINAL, RREF));
      t2.update(therm1.temperature(RNOMINAL, RREF));
      t3.update(therm1.temperature(RNOMINAL, RREF));
      t4.update(therm1.temperature(RNOMINAL, RREF));
      t5.update(therm1.temperature(RNOMINAL, RREF));
      t6.update(therm1.temperature(RNOMINAL, RREF));
      t7.update(therm1.temperature(RNOMINAL, RREF));
      t8.update(therm1.temperature(RNOMINAL, RREF));
      t9.update(therm1.temperature(RNOMINAL, RREF));
      t10.update(sht20.readTemperature());
      h1.update(sht20.readHumidity());
      irr.update(readVoltage(0));
      lastReadMillis = millis();
    }
    if (millis() - lastUploadMillis >= uploadInterval)
    {
      String json = "{\"t1\":\"" + String(t1.average()) +
                    "\" , \"t2\":\"" + String(t2.average()) +
                    "\" , \"t3\":\"" + String(t3.average()) +
                    "\" , \"t4\":\"" + String(t4.average()) +
                    "\" , \"t5\":\"" + String(t5.average()) +
                    "\" , \"t6\":\"" + String(t6.average()) +
                    "\" , \"t7\":\"" + String(t7.average()) +
                    "\" , \"t8\":\"" + String(t8.average()) +
                    "\" , \"t9\":\"" + String(t9.average()) +
                    "\" , \"t10\":\"" + String(t10.average()) +
                    "\" , \"h1\":\"" + String(h1.average()) +
                    "\" , \"irr\":\"" + String(irr.average()) + "\" }";

      char *payload = &json[0]; // converts String to char*
      mqttClient.publish(input_topic, payload);
      mqttClient.loop(); //      give control to MQTT to send message to broker

      lastUploadMillis = millis();
    }
    mqttClient.loop();
  }
}