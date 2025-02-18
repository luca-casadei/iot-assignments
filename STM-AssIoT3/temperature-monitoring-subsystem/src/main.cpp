#include <WiFi.h>
#include <PubSubClient.h>
#include "./wifi/wifi_manager.hpp"
#include "./mqtt/MQTTManager.hpp"
#include "./devices/TempSensor.hpp"
#include "./devices/TempSensorLM35.hpp"
#include "./devices/Led.hpp"
#include "./config.hpp"


#define MSG_BUFFER_SIZE  50

MQTTManager mqttManager("broker.mqtt-dashboard.com", 1883, "casapazz-temperature");
TempSensor* tempSensor;
Led* greenLed;
Led* redLed;

unsigned long lastMsgTime = 0;
char msg[MSG_BUFFER_SIZE];
int tempValue = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  randomSeed(micros());
  mqttManager.begin();
  tempSensor = new TempSensorLM35(TEMP_SENSOR_PIN);
  greenLed = new Led(GREEN_LED_PIN);
  redLed = new Led(RED_LED_PIN);
}

void loop() {
  mqttManager.connect(); 

  unsigned long now = millis();
  if (now - lastMsgTime > 100) {
    lastMsgTime = now;
    tempValue = tempSensor->getTemperature();
    snprintf(msg, MSG_BUFFER_SIZE, "Temperature: %ld°C", tempValue);
    Serial.println(msg);
    mqttManager.publishMessage(msg);
  }
}
