package it.unibo.iot.history;

import io.vertx.core.AbstractVerticle;

import static it.unibo.iot.Configuration.T1;
import static it.unibo.iot.Configuration.T2;
import static it.unibo.iot.Configuration.DTSeconds;

import java.util.ArrayList;
import java.util.List;

public final class ControlUnit extends AbstractVerticle {
    private final int len;
    private final List<Float> temperatures;
    private State currentState;
    private Mode currentMode;
    private long firstTooHotTime = 0;

    public ControlUnit(final int listLength) {
        temperatures = new ArrayList<>();
        this.len = listLength;
        this.currentState = State.NORMAL;
        this.currentMode = Mode.AUTOMATIC;
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
                if ((currentTime - firstTooHotTime) > DTSeconds * 1000) {
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
            vertx.eventBus().send("serial.mode.send", currentMode);
            vertx.eventBus().send("serial.state.send", currentState);
            vertx.eventBus().send("serial.temperature.send", temperature);
            //System.out.println("Aggiunta temperatura: " + temperature);
        });
        vertx.eventBus().consumer("state.get", message -> {
            message.reply(currentState);
        });
        vertx.eventBus().consumer("mode.change", _ -> {
            if (this.currentMode == Mode.AUTOMATIC) {
                this.currentMode = Mode.MANUAL;
                this.currentState = State.CONTROLLING;
            } else {
                this.currentMode = Mode.AUTOMATIC;
                this.currentState = State.NORMAL;
            }
        });
    }
}
