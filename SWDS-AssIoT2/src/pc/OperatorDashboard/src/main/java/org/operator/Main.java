package org.operator;

import org.operator.components.SerialCommunication;
import org.operator.view.ContainerGUI;

public class Main {
    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(() -> {

            ContainerGUI gui = new ContainerGUI();
            gui.setVisible(true);

            // Configura la comunicazione seriale
            SerialCommunication serial = new SerialCommunication(" /dev/cu.usbmodem11301");
            if (serial.open()) {
                serial.setDataListener(data -> {

                    try {
                        int distance = Integer.parseInt(data);
                        // gui.updateContainer(distance);
                    } catch (NumberFormatException e) {
                        System.err.println("Dati ricevuti non validi: " + data);
                    }
                });
            }
        });
    }
}