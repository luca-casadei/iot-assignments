package it.unibo.iot.mqtt;

import io.vertx.core.AbstractVerticle;
import io.vertx.mqtt.MqttClient;

import static it.unibo.iot.Configuration.BROKER_ADDRESS;
import static it.unibo.iot.Configuration.TOPIC_NAME;

/*
 * MQTT Agent
 */
public class MQTTAgent extends AbstractVerticle {
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