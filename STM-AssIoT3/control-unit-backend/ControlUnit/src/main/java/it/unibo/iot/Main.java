package it.unibo.iot;

import it.unibo.iot.mqtt.MQTTAgent;
import it.unibo.iot.mqtt.MQTTServer;
import it.unibo.iot.serial.SerialCommChannel;
import jssc.SerialPortException;

public class Main {
    private final static String SERIAL_PORT = "/dev/ttyACM0";
    private final static int SERIAL_RATE = 9600;
    public static void main(String[] args) {
        final MQTTServer mqttServer = new MQTTServer();
        final Thread mqttServerThread = new Thread(mqttServer);
        mqttServerThread.start();
        final MQTTAgent mqttClient = new MQTTAgent();
        final Thread mqttClientThread = new Thread(mqttClient);
        mqttClientThread.start();
        try {
            final SerialCommChannel serial = new SerialCommChannel(SERIAL_PORT,SERIAL_RATE);
            final Thread serialThread = new Thread(serial);
            serialThread.start();
        } catch (SerialPortException e) {
            throw new IllegalStateException("Port invalid or busy");
        }
    }
}
