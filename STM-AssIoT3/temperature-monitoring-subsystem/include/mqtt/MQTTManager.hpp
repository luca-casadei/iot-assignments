#pragma once

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTManager {
public:
    MQTTManager(const char* server, uint16_t port, const char* topic);

    void begin();

    void connect();

    void publishMessage(const char* msg);

private:
    static MQTTManager* instance;

    WiFiClient m_espClient;
    PubSubClient m_client;

    uint16_t m_port;
    const char* m_topic;
    const char* m_server;

    void handleMessage(char* topic, uint8_t* payload, unsigned int length);

    static void mqttCallback(char* topic, byte* payload, unsigned int length);
};
