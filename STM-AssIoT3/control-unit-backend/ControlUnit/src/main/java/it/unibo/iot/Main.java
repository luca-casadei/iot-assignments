package it.unibo.iot;

import io.vertx.core.*;
import it.unibo.iot.http.HTTPServer;
import it.unibo.iot.mqtt.MQTTAgent;
import it.unibo.iot.serial.SerialCommChannel;

import java.util.List;

public class Main {
    private final static String SERIAL_PORT = "/dev/ttyACM0";
    private final static int SERIAL_RATE = 9600;

    public static void main(String[] args) {
        final Vertx vertx = Vertx.vertx();
        Future.all(
                        List.of(
                                vertx.deployVerticle(new HTTPServer()),
                                vertx.deployVerticle(new MQTTAgent()),
                                vertx.deployVerticle(new SerialCommChannel(SERIAL_PORT, SERIAL_RATE),
                                        new DeploymentOptions().setThreadingModel(ThreadingModel.WORKER))
                        )
                ).onFailure(res -> {
                    System.out.println("Errore nel deployment dei demoni");
                    vertx.close();
                })
                .onComplete(res -> {
                            System.out.println("Deployment dei demoni eseguito con successo.");
                        }
                );
    }
}
