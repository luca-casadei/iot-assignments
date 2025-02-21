package it.unibo.iot.history;

import io.vertx.core.AbstractVerticle;

import static it.unibo.iot.Configuration.T1;
import static it.unibo.iot.Configuration.T2;
import static it.unibo.iot.Configuration.DTSeconds;

import java.util.ArrayList;
import java.util.List;

public final class History extends AbstractVerticle {
    private final int len;
    private final List<Float> temperatures;
    private State currentState;
    private long firstTooHotTime = 0;

    public History(final int listLength) {
        temperatures = new ArrayList<>();
        this.len = listLength;
        this.currentState = State.NORMAL;
    }

    private void addTemperatureToList(final float temperature) {
        temperatures.addFirst(temperature);
        if (temperatures.size() > len) {
            temperatures.removeLast();
        }
    }

    private void checkTemperatureForState(final float temperature) {
        if (temperature < T1) {
            this.currentState = State.NORMAL;
        } else if (temperature <= T2) {
            this.currentState = State.HOT;
        } else if (temperature > T2) {
            if (this.currentState == State.TOO_HOT) {
                final long currentTime = System.currentTimeMillis();
                if ((currentTime - firstTooHotTime) > DTSeconds * 1000){
                    currentState = State.ALARM;
                }
            } else {
                this.currentState = State.TOO_HOT;
                firstTooHotTime = System.currentTimeMillis();
            }
        }
    }

    @Override
    public void start() {
        vertx.eventBus().consumer("temperature.add", t -> {
            final float temperature = Float.parseFloat(t.body().toString());
            addTemperatureToList(temperature);
            checkTemperatureForState(temperature);
            System.out.println("Aggiunta temperatura: " + temperature);
        });
    }


}
