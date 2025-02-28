package it.unibo.iot.http;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.handler.BodyHandler;
import it.unibo.iot.history.Mode;
import it.unibo.iot.history.State;

public class HTTPServer extends AbstractVerticle {
    private final Router router = Router.router(vertx);
    private float currentTemperature;
    private State currentState;
    private Mode currentMode;
    private int windowPercentage;

    @Override
    public void start() {
        router.route().handler(BodyHandler.create());

        getSystemInfo();
        toggleMode();
        moveWindow();
        resetAlarm();
        globalListener();

        vertx.eventBus().consumer("http.data.send", t -> {
            final String[] data = t.body().toString().split(":");
            currentTemperature = Float.parseFloat(data[0]);
            currentState = State.valueOf(data[1]);
            currentMode = Mode.valueOf(data[2]);
            windowPercentage = Integer.parseInt(data[3]);
        });

        vertx.createHttpServer()
                .requestHandler(this.router)
                .listen(8080)
                .onSuccess(server -> System.out.println("HTTP server started on port " + server.actualPort()))
                .onFailure(Throwable::printStackTrace);
    }

    private void globalListener() {
        this.router.route().handler(ctx -> {
            System.out.println("Request received from" + ctx.request().remoteAddress());
            ctx.next();
        });
    }

    private void getSystemInfo() {
        this.router.route(HttpMethod.GET, "/info")
                .handler(ctx -> {
                    HttpServerResponse response = ctx.response();
                    response.putHeader("Content-Type", "text/plain")
                            .end(String.format("{\"temperature\": \"%s\",\"state\":\"%s\",\"mode\":\"%s\",\"window_opening\":\"%s\"}", currentTemperature, currentState, currentMode, windowPercentage));
                });
    }

    private void toggleMode() {
        this.router.route(HttpMethod.POST, "/toggle_mode")
                .consumes("application/json")
                .handler(ctx -> {
                    vertx.eventBus().send("mode.change", "");
                    ctx.response()
                            .putHeader("Content-Type", "text/plain")
                            .end("Mode changed");
                });
    }

    private void moveWindow() {
        this.router.route(HttpMethod.POST, "/move_window")
                .consumes("application/json")
                .handler(ctx -> {
                    final JsonObject body = ctx.body().asJsonObject();
                    System.out.println(body);
                    if (body == null || !body.containsKey("window")) {
                        ctx.response()
                                .setStatusCode(400)
                                .putHeader("Content-Type", "text/plain")
                                .end("Invalid JSON: missing 'window' key");
                        return;
                    }
                    final Integer windowValue = Integer.parseInt(body.getString("window"));
                    vertx.eventBus().send("http.window.send", windowValue);
                    ctx.response()
                            .putHeader("Content-Type", "text/plain")
                            .end("Window: " + windowValue);
                });
    }

    private void resetAlarm() {
        this.router.route(HttpMethod.POST, "/reset")
                .consumes("application/json")
                .handler(ctx -> {
                    vertx.eventBus().send("alarm.reset", "");
                    ctx.response()
                            .putHeader("Content-Type", "text/plain")
                            .end("Alarm reset");
                });
    }
}
