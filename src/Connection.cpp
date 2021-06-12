// #include <Connection.h>
// #include <credentials.h>

// Connection::Connection(int16_t messageSize)
// {
//     unsigned long waitCount;
//     uint8_t status;
//     String clientId;

//     WiFiClient espClient;
//     MQTTClient mqttClient(messageSize);
//     StaticJsonDocument<256> jsonDoc;
//     char payload[256];
// }

// // void initConnection()
// // {
// //     WiFi.mode(WIFI_STA); // config WiFi as client
// // }

// boolean Connection::statusOK()
// {
//     // Connection status for WiFi and MQTT:
//     //
//     // status |   WiFi   |    MQTT
//     // -------+----------+------------
//     //      0 |   down   |    down
//     //      1 | starting |    down
//     //      2 |    up    |    down
//     //      3 |    up    |  starting
//     //      4 |    up    | finalising
//     //      5 |    up    |     up
//     if ((WiFi.status() != WL_CONNECTED) && (status != 1))
//     {
//         status = 0;
//     }
//     if ((WiFi.status() == WL_CONNECTED) && !mqttClient.connected() && (status != 3))
//     {
//         status = 2;
//     }
//     if ((WiFi.status() == WL_CONNECTED) && mqttClient.connected() && (status != 5))
//     {
//         status = 4;
//     }
//     switch (status)
//     {
//     case 0: // MQTT and WiFi down: start WiFi
//         Serial.println("MQTT and WiFi down: start WiFi");
//         WiFi.begin(WiFi_SSID, WiFi_PW);
//         status = 1;
//         break;
//     case 1: // WiFi starting, do nothing here
//         Serial.print("WiFi starting, wait : ");
//         Serial.println(waitCount);
//         waitCount++;
//         break;
//     case 2: // WiFi up, MQTT down: start MQTT
//         Serial.println("WiFi up, MQTT down: start MQTT");
//         mqttClient.begin(mqtt_broker, 1883, espClient);          //   config MQTT Server, use port 8883 for secure connection
//         clientId = "ESP32Client-" + String(random(0xffff), HEX); // Create a random client ID
//         mqttClient.connect(clientId.c_str(), mqtt_user, mqtt_pw);
//         status = 3;
//         waitCount = 0;
//         break;
//     case 3: // WiFi up, MQTT starting, do nothing here
//         Serial.print("WiFi up, MQTT starting, wait : ");
//         Serial.println(waitCount);
//         mqttClient.connect(clientId.c_str(), mqtt_user, mqtt_pw);
//         waitCount++;
//         break;
//     case 4: // WiFi up, MQTT up: finish MQTT configuration
//         Serial.println("WiFi up, MQTT up: finish MQTT configuration");
//         mqttClient.publish(input_topic, "{\"Status\":\"up and running!\"}");
//         status = 5;
//         break;
//     }
//     return status == 5;
// }

// void Connection::upload()
// {
//     serializeJson(jsonDoc, payload);
//     mqttClient.publish(input_topic, payload);
//     mqttClient.loop(); //      give control to MQTT to send message to broker
// }

// void Connection::check()
// {
//     mqttClient.loop();
// }
