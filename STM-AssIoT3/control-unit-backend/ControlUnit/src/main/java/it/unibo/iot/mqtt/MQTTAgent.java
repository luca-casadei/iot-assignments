package it.unibo.iot.mqtt;

import io.vertx.core.AbstractVerticle;
import io.vertx.mqtt.MqttClient;

/*
 * MQTT Agent
 */
public class MQTTAgent extends AbstractVerticle {

    private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com";
    private static final String TOPIC_NAME = "esiot-casadeipazzaglia-temperature";

    @Override
    public void start() {
        final MqttClient client = MqttClient.create(vertx);
        client.connect(1883, BROKER_ADDRESS, _ -> {
            log("connected");
            log("subscribing...");
            client.publishHandler(s -> vertx.eventBus().send("temperature.add", Float.parseFloat(s.payload().toString())))
                    .subscribe(TOPIC_NAME, 2);
        });
    }

    private void log(String msg) {
        System.out.println("[MQTT AGENT] " + msg);
    }
}