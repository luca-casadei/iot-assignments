package it.unibo.iot;

public final class Configuration {
    public final static int DTSeconds = 10;
    public final static float T1 = 15.0f;
    public final static float T2 = 18.0f;
    public final static int F1MS = 1500;
    public final static int F2MS = 1000;
    public final static String SERIAL_PORT = "/dev/ttyACM0";
    public final static int SERIAL_RATE = 115200;
    public final static int HISTORY_LEN = 50;
    public static final String BROKER_ADDRESS = "broker.hivemq.com";
    public static final String TOPIC_NAME = "esiot-casadeipazzaglia-temperature";
}
