package it.unibo.iot.serial;

import java.util.concurrent.*;

import io.vertx.core.AbstractVerticle;
import jssc.*;

/**
 * Comm channel implementation based on serial port.
 *
 * @author aricci
 */
public class SerialCommChannel extends AbstractVerticle implements CommChannel, SerialPortEventListener {
    private final SerialPort serialPort;
    private final BlockingQueue<String> queue;
    private StringBuffer currentMsg = new StringBuffer();
    private volatile boolean running;

    public SerialCommChannel(String port, int rate) {
        queue = new ArrayBlockingQueue<>(100);

        serialPort = new SerialPort(port);
        try {
            serialPort.openPort();

            serialPort.setParams(rate,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);

            serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN |
                    SerialPort.FLOWCONTROL_RTSCTS_OUT);

            serialPort.addEventListener(this);
        } catch (SerialPortException ex) {
            throw new IllegalStateException(ex.getMessage());
        }

    }

    @Override
    public void sendMsg(String msg) {
        char[] array = (msg + "\n").toCharArray();
        byte[] bytes = new byte[array.length];
        for (int i = 0; i < array.length; i++) {
            bytes[i] = (byte) array[i];
        }
        try {
            synchronized (serialPort) {
                serialPort.writeBytes(bytes);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
    }

    @Override
    public String receiveMsg() throws InterruptedException {
        return queue.take();
    }

    @Override
    public boolean isMsgAvailable() {
        return !queue.isEmpty();
    }

    /**
     * This should be called when you stop using the port.
     * This will prevent port locking on platforms like Linux.
     */
    public void close() {
        try {
            if (serialPort != null) {
                serialPort.removeEventListener();
                serialPort.closePort();
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
    }


    public void serialEvent(SerialPortEvent event) {
        /* if there are bytes received in the input buffer */
        if (event.isRXCHAR()) {
            try {
                String msg = serialPort.readString(event.getEventValue());

                msg = msg.replaceAll("\r", "");

                currentMsg.append(msg);

                boolean goAhead = true;

                while (goAhead) {
                    String msg2 = currentMsg.toString();
                    int index = msg2.indexOf("\n");
                    if (index >= 0) {
                        queue.put(msg2.substring(0, index));
                        currentMsg = new StringBuffer();
                        if (index + 1 < msg2.length()) {
                            currentMsg.append(msg2.substring(index + 1));
                        }
                    } else {
                        goAhead = false;
                    }
                }

            } catch (Exception ex) {
                System.out.println("Error in receiving string from COM-port: " + ex.getMessage());
            }
        }
    }

    @Override
    public void start() {
        System.out.println("Serial started on port: " + serialPort.getPortName());
        vertx.eventBus().consumer("serial.state.send", t -> {
            sendMsg(t.body().toString());
        });
        vertx.eventBus().consumer("serial.temperature.send", t -> {
            sendMsg("TEMPERATURE:" + t.body().toString());
        });
        vertx.eventBus().consumer("serial.mode.send", t -> {
            sendMsg("MODE:" + t.body().toString());
        });
        vertx.executeBlocking(promise -> {
            while (running) {
                try {
                    final String msg = queue.take();
                    if (msg.equals("MODE:CHANGE")){
                        vertx.eventBus().send("mode.change", "");
                    }
                    else{
                        final double potValue = Double.parseDouble(msg);
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
            promise.complete();
        }, false);
    }

    @Override
    public void stop() {
        running = false;
        close();
    }
}