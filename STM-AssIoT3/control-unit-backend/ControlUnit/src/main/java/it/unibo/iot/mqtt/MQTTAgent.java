package it.unibo.iot.mqtt;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;

/*
 * MQTT Agent
 */
public class MQTTAgent extends AbstractVerticle implements Runnable {
	
	private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com";
	private static final String TOPIC_NAME = "esiot-2024";

	@Override
	public void start() {
		final MqttClient client = MqttClient.create(vertx);
		
		client.connect(1883, BROKER_ADDRESS, _ -> {

			log("connected");
			
			log("subscribing...");
			client.publishHandler(s -> {
			  System.out.println("There are new message in topic: " + s.topicName());
			  System.out.println("Content(as string) of the message: " + s.payload().toString());
			  System.out.println("QoS: " + s.qosLevel());
			})
			.subscribe(TOPIC_NAME, 2);		

			log("publishing a msg");
			client.publish(TOPIC_NAME,
				  Buffer.buffer("hello"),
				  MqttQoS.AT_LEAST_ONCE,
				  false,
				  false);
		});
	}
	

	private void log(String msg) {
		System.out.println("[MQTT AGENT] "+msg);
	}

	@Override
	public void run() {
		Vertx vertx = Vertx.vertx();
		vertx.deployVerticle(this);
	}
}