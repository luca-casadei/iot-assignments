package it.unibo.iot.history;

import io.vertx.core.AbstractVerticle;

import java.util.ArrayList;
import java.util.List;

import static it.unibo.iot.Configuration.*;

public final class ControlUnit extends AbstractVerticle {
    private final int len;
    private final List<Float> temperatures;
    private int windowPercentage;
    private int dashboardPercentage;
    private State currentState;
    private Mode currentMode;
    private long firstTooHotTime = 0;
    private int frequency;

    public ControlUnit(final int listLength) {
        temperatures = new ArrayList<>();
        this.len = listLength;
        this.currentState = State.NORMAL;
        this.currentMode = Mode.AUTOMATIC;
        this.frequency = F1MS;
        this.dashboardPercentage = -1;
        this.windowPercentage = 1;
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
            this.frequency = F1MS;
        } else if (temperature <= T2) {
            this.currentState = State.HOT;
            this.frequency = F2MS;
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
            if (currentMode == Mode.AUTOMATIC && currentState != State.ALARM) {
                checkTemperatureForState(temperature);
            }
            vertx.eventBus().send("mqtt.freq.send", "FREQ:" + this.frequency);
            vertx.eventBus().send("serial.data.send", temperature + ":"
                    + currentState + ":" + currentMode + ":" + dashboardPercentage);
            vertx.eventBus().send(
                    "http.data.send",
                    temperature + ":" + currentState + ":" + currentMode + ":" + windowPercentage + ":"
                            + temperatures.stream().mapToDouble(Float::doubleValue).average().orElse(0) + ":"
                            + temperatures.stream().max(Float::compare).orElse(0.0f) + ":"
                            + temperatures.stream().min(Float::compare).orElse(0.0f) + ":" + this.frequency);
            dashboardPercentage = -1;
        });
        vertx.eventBus().consumer("serial.window.percentage", p -> {
            this.windowPercentage = Integer.parseInt(p.body().toString());
        });
        vertx.eventBus().consumer("http.window.send", w -> {
            dashboardPercentage = Integer.parseInt(w.body().toString());
        });
        vertx.eventBus().consumer("alarm.reset", _ -> {
            if (this.currentMode == Mode.AUTOMATIC && this.currentState == State.ALARM) {
                this.currentState = State.NORMAL;
            }
        });
        vertx.eventBus().consumer("state.get", message -> message.reply(currentState));
        vertx.eventBus().consumer("mode.change", _ -> {
            if (this.currentState != State.ALARM) {
                if (this.currentMode == Mode.AUTOMATIC) {
                    this.currentMode = Mode.MANUAL;
                    this.currentState = State.CONTROLLING;
                } else {
                    this.currentMode = Mode.AUTOMATIC;
                    this.currentState = State.NORMAL;
                }
            }
        });
    }
}
