#include "./mqtt/MQTTManager.hpp"
#include "./config.hpp"

MQTTManager* MQTTManager::instance = nullptr;

MQTTManager::MQTTManager(const char* server,const char* server_secondary, uint16_t port, const char* topic)
  : m_client(m_espClient), m_server_secondary(server_secondary), m_server(server), m_port(port), m_topic(topic)
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
    unsigned int tries = 0;
    bool primary = true;
    while (!m_client.connected() && tries < MAX_CONNECTION_TRIES) {
      Serial.print("Attempting MQTT connection...");
      String clientId = String("temperature-esiot25pc-client-") + String(random(0xffff), HEX);
      
      if (m_client.connect(clientId.c_str())) {
        Serial.println("connected");
        m_client.subscribe(m_topic);
      } else {
        Serial.print("failed, rc=");
        Serial.print(m_client.state());
        Serial.println(" - trying again in 5 seconds");
        tries++;
        delay(5000);
      }
      if(tries == MAX_CONNECTION_TRIES && primary){
        primary = false;
        m_client.setServer(this->m_server_secondary, this->m_port);
      }
    }

  }
  m_client.loop();
}

bool MQTTManager::isConnected() {
  return m_client.connected();
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
