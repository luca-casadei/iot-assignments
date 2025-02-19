package it.unibo.iot.history;

import io.vertx.core.AbstractVerticle;

import java.util.ArrayList;
import java.util.List;

public final class History extends AbstractVerticle {
    private final List<Float> temperatures;

    public History() {
        temperatures = new ArrayList<>();
    }

    @Override
    public void start() {
        vertx.eventBus().consumer("temperature.add", t -> {
            final Float temperature = Float.parseFloat(t.body().toString());
            temperatures.add(temperature);
            System.out.println("Aggiunta temperatura: " + temperature);
        });
    }
}
