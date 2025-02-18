package it.unibo.iot.http;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.ext.web.Router;

public class HTTPServer extends AbstractVerticle {
    private final Router router = Router.router(vertx);

    @Override
    public void start() {
        getSystemInfo();

        toggleMode();

        resetAlarm();

        globalListener();

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
                            .end("PROVA RISPOSTA getSystemInfo\n");
                });

    }

    private void toggleMode() {
        this.router.route(HttpMethod.POST, "/toggle_mode")
                .consumes("application/json")
                .handler(ctx -> {
                    HttpServerResponse response = ctx.response();
                    response.putHeader("Content-Type", "text/plain")
                            .end("PROVA RISPOSTA toggleMode\n");
                });
    }

    private void resetAlarm() {
        this.router.route(HttpMethod.POST, "/reset")
                .consumes("application/json")
                .handler(ctx -> {
                    HttpServerResponse response = ctx.response();
                    response.putHeader("Content-Type", "text/plain")
                            .end("PROVA RISPOSTA resetAlarm\n");
                });
    }
}
