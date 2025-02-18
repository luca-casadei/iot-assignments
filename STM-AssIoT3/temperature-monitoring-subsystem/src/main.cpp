#include <WiFi.h>
#include <PubSubClient.h>
#include "./wifi/wifi_manager.hpp"
#include "./mqtt/MQTTManager.hpp"
#define MSG_BUFFER_SIZE  50

MQTTManager mqttManager("broker.mqtt-temperature-monitoring.com", 1883, "temperature");

unsigned long lastMsgTime = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  randomSeed(micros());
  mqttManager.begin();
}

void loop() {
  mqttManager.connect(); 

  unsigned long now = millis();
  if (now - lastMsgTime > 100) {
    lastMsgTime = now;
    value++;

    snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    mqttManager.publishMessage(msg);
  }
}
