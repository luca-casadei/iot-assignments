package org.operator.components;

import jssc.SerialPort;
import jssc.SerialPortException;

public class SerialCommunication {
    private SerialPort serialPort;
    private DataListener dataListener;

    public SerialCommunication(String portName) {
        serialPort = new SerialPort(portName);
    }

    public boolean open() {
        try {
            if (serialPort.openPort()) {
                serialPort.setParams(
                        SerialPort.BAUDRATE_9600,
                        SerialPort.DATABITS_8,
                        SerialPort.STOPBITS_1,
                        SerialPort.PARITY_NONE
                );
                startListening();
                return true;
            }
        } catch (SerialPortException e) {
            System.err.println("Errore apertura porta seriale: " + e.getMessage());
        }
        return false;
    }

    private void startListening() {
        new Thread(() -> {
            while (serialPort.isOpened()) {
                try {
                    byte[] buffer = serialPort.readBytes();
                    if (buffer != null && buffer.length > 0) {
                        String data = new String(buffer).trim();
                        if (dataListener != null) {
                            dataListener.onDataReceived(data);
                        }
                    }
                } catch (SerialPortException e) {
                    System.err.println("Errore lettura seriale: " + e.getMessage());
                }
            }
        }).start();
    }

    public void setDataListener(DataListener listener) {
        this.dataListener = listener;
    }

    public void close() {
        try {
            if (serialPort.isOpened()) {
                serialPort.closePort();
            }
        } catch (SerialPortException e) {
            System.err.println("Errore chiusura porta seriale: " + e.getMessage());
        }
    }

    public interface DataListener {
        void onDataReceived(String data);
    }
}
