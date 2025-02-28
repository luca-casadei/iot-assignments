#pragma once

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTManager {
public:
    MQTTManager(const char* server, const char *server_secondary, uint16_t port, const char* topic);

    void begin();

    void connect();

    bool isConnected();

    void publishMessage(const char* msg);

private:
    static MQTTManager* instance;

    WiFiClient m_espClient;
    PubSubClient m_client;

    uint16_t m_port;
    const char* m_topic;
    const char* m_server;
    const char* m_server_secondary;

    void handleMessage(char* topic, uint8_t* payload, unsigned int length);

    static void mqttCallback(char* topic, byte* payload, unsigned int length);
};
