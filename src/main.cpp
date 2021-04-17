#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MAX31865.h>
#include <WiFi.h>
#include <MQTTClient.h> // MQTT Client from Joël Gaehwiler https://github.com/256dpi/arduino-mqtt   keepalive manually to 15s
#include <Measurement.h>

const char* WiFi_SSID = "YourWiFiSSID";           // change according your setup : SSID and password for the WiFi network
const char* WiFi_PW = "YourWiFiPassword";         //    "
const char* mqtt_broker = "YourMQTTBrokerIP";     // change according your setup : IP Adress or FQDN of your MQTT broker
const char* mqtt_user = "YourMQTTBrokerUsername"; // change according your setup : username and password for authenticated broker access
const char* mqtt_pw = "YourMQTTBrokerPassword";   //    "
const char* input_topic = "YourTopic";            // change according your setup : MQTT topic for messages from device to broker

const int stationID = 3; // check stations table in database
long readInterval = 3000;
unsigned long uploadInterval = 10000;

long lastReadMillis;
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

// Use software SPI: CS, DI, DO, CLK
// Adafruit_MAX31865 maxe = Adafruit_MAX31865(15, 18, 4, 5); // As marked on board

// use hardware SPI, just pass in the CS pin
// Use print_spi_pins() to find your board defaults
Adafruit_MAX31865 therm1 = Adafruit_MAX31865(4);  // As marked on board
Adafruit_MAX31865 therm2 = Adafruit_MAX31865(5);  // As marked on board
Adafruit_MAX31865 therm3 = Adafruit_MAX31865(13); // As marked on board
Adafruit_MAX31865 therm4 = Adafruit_MAX31865(14); // As marked on board
Adafruit_MAX31865 therm5 = Adafruit_MAX31865(27); // As marked on board
Adafruit_MAX31865 therm6 = Adafruit_MAX31865(26); // As marked on board
Adafruit_MAX31865 therm7 = Adafruit_MAX31865(25); // As marked on board
Adafruit_MAX31865 therm8 = Adafruit_MAX31865(33); // As marked on board
Adafruit_MAX31865 therm9 = Adafruit_MAX31865(32); // As marked on board
// Adafruit_MAX31865 therm2 = Adafruit_MAX31865(4);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF 4300.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL 1000.0

Measurement t1;
Measurement t2;
Measurement t3;
Measurement t4;
Measurement t5;
Measurement t6;
Measurement t7;
Measurement t8;
Measurement t9;


void printSpiPins()
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

void setup()
{
  Serial.begin(115200);
  printSpiPins();
  WiFi.mode(WIFI_STA);          // config WiFi as client
  therm1.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm2.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm3.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm4.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm5.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm6.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm7.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm8.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary
  therm9.begin(MAX31865_4WIRE); // set to 2WIRE or 4WIRE as necessary

}

void loop()
{
  if (connected())
  {
    if (millis() - lastReadMillis > readInterval)
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
      // Serial.println(temperature.toString());
      lastReadMillis = millis();
    }
    if (millis() - lastUploadMillis > uploadInterval)
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
                    "\", \"stationID\":\"" + stationID + "\" }";

      char *payload = &json[0]; // converts String to char*
      mqttClient.publish(input_topic, payload);
      mqttClient.loop(); //      give control to MQTT to send message to broker

      lastUploadMillis = millis();
    }
    mqttClient.loop();
  }
}