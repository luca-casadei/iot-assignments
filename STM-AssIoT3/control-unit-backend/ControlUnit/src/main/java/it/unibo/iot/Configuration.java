package it.unibo.iot;

public final class Configuration {
    public final static int DTSeconds = 10;
    public final static float T1 = 15.0f;
    public final static float T2 = 18.0f;
    public final static String SERIAL_PORT = "/dev/ttyACM0";
    public final static int SERIAL_RATE = 115200;
    public final static int HISTORY_LEN = 100;
    public static final String BROKER_ADDRESS = "broker.emqx.io";
    public static final String TOPIC_NAME = "esiot-casadeipazzaglia-temperature";
}
