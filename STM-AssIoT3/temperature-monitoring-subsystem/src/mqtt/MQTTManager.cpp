#include "./mqtt/MQTTManager.hpp"

MQTTManager* MQTTManager::instance = nullptr;

MQTTManager::MQTTManager(const char* server, uint16_t port, const char* topic)
  : m_client(m_espClient), m_server(server), m_port(port), m_topic(topic)
{
  if (instance == nullptr) {
    instance = this;
  }
}

void MQTTManager::begin() {
  Serial.println(m_server);
  m_client.setServer(m_server, m_port);
  m_client.setCallback(mqttCallback);
}

void MQTTManager::connect() {
  if (!m_client.connected()) {
    while (!m_client.connected()) {
      Serial.print("Attempting MQTT connection...");
      String clientId = String("temperature-client-") + String(random(0xffff), HEX);
      
      if (m_client.connect(clientId.c_str())) {
        Serial.println("connected");
        m_client.subscribe(m_topic);
      } else {
        Serial.print("failed, rc=");
        Serial.print(m_client.state());
        Serial.println(" - trying again in 5 seconds");
        delay(5000);
      }
    }
  }
  m_client.loop();
}

void MQTTManager::publishMessage(const char* msg) {
  m_client.publish(m_topic, msg);
}

void MQTTManager::handleMessage(char* topic, uint8_t* payload, unsigned int length) {
  Serial.println(String("Message arrived on [") + topic + "] len: " + length);
}

void MQTTManager::mqttCallback(char* topic, byte* payload, unsigned int length) {
  if (instance != nullptr) {
    instance->handleMessage(topic, payload, length);
  }
}
