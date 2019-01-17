#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include "FS.h"

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;
Ticker wifiReconnectTimer;

String host="TTIOT-SmartSocket8";
String ssid = "";
String password = "";
IPAddress myIp;
String mac;

#define MQTT_HOST "broker.hivemq.com"
#define MQTT_PORT 1883

StaticJsonBuffer<500> jsonBuffer;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  Serial.println("DEBUG: Entering loadConfig()");
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
  }
  Serial.println();
  Serial.println();
//  saveConfig();
  delay(1000);
  Serial.println("Configuaration saved");
  loadConfig();
  Serial.println("DEBUG: loadConfig() passed");
  
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
//  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  connectToWifi();
  switch_setup();
}

void loop() {
}
