package org.operator.components;

import com.fazecast.jSerialComm.SerialPort;

public final class SerialCommunication {
    private final SerialPort serialPort;

    public SerialCommunication() {
        serialPort = SerialPort.getCommPort("COM4");
        serialPort.setComPortParameters(9600, 8, 1, SerialPort.NO_PARITY);
        serialPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 1000, 1000);

        if (serialPort.openPort()) {
            System.out.println("Serial port opened");
        } else {
            System.err.println("Failed to open serial port");
        }
    }

    public void sendMessage(final String message) {
        if (serialPort.isOpen()) {
            byte[] messageBytes = (message + "\n").getBytes();
            serialPort.writeBytes(messageBytes, messageBytes.length);
            System.out.println("Sent message: " + message);
        }
    }

    public String readData() {
        if (serialPort.isOpen()) {
            byte[] readBuffer = new byte[1024];
            int numRead = serialPort.readBytes(readBuffer, readBuffer.length);
            return new String(readBuffer, 0, numRead).trim();
        }
        return null;
    }

    public void close() {
        if (serialPort.isOpen()) {
            serialPort.closePort();
        }
    }
}
