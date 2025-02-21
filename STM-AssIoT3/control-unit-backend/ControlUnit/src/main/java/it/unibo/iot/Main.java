package it.unibo.iot;

import io.vertx.core.*;
import it.unibo.iot.history.ControlUnit;
import it.unibo.iot.http.HTTPServer;
import it.unibo.iot.mqtt.MQTTAgent;
import it.unibo.iot.serial.SerialCommChannel;

import java.util.List;

import static it.unibo.iot.Configuration.SERIAL_RATE;
import static it.unibo.iot.Configuration.HISTORY_LEN;
import static it.unibo.iot.Configuration.SERIAL_PORT;

public class Main {
    public static void main(String[] args) {
        final Vertx vertx = Vertx.vertx();
        Future.all(
                        List.of(
                                vertx.deployVerticle(new ControlUnit(HISTORY_LEN)),
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
