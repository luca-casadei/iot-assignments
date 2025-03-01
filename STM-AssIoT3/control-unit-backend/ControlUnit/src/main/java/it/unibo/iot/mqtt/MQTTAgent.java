package it.unibo.iot.mqtt;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.buffer.Buffer;
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
            client.publishHandler(s -> {
                        final String payload = s.payload().toString();
                        if (!payload.startsWith("FREQ")) {
                            vertx.eventBus().send("temperature.add", Float.parseFloat(payload));
                        }
                    })
                    .subscribe(TOPIC_NAME, 2);
        });
        vertx.eventBus().consumer("mqtt.freq.send", freqM -> {
            client.publish(TOPIC_NAME, Buffer.buffer().appendString(freqM.body().toString()), MqttQoS.valueOf(2), false, false);
        });
    }

    private void log(String msg) {
        System.out.println("[MQTT AGENT] " + msg);
    }
}