package org.operator.controller;

import org.operator.components.SerialCommunication;
import org.operator.model.Container;
import org.operator.view.SensorView;

public final class SensorController {
    private final SensorView view;
    private final SerialCommunication serialCommunication;
    private final Container container;

    public SensorController(final Container container, final SensorView view) {
        this.view = view;
        this.container = container;

        serialCommunication = new SerialCommunication();

        view.addEmptyButtonListener(e -> serialCommunication.sendMessage("EMPTY"));
        view.addRestoreButtonListener(e -> serialCommunication.sendMessage("RESTORE"));
        view.setVisible(true);
    }

    public void startUpdatingView() {
        new Thread(() -> {
            while (true) {
                final String data = serialCommunication.readData();
                if (data != null) {
                    final String[] values = data.split(",");
                    if (values.length == 2) {
                        try {
                            final double temp = Double.parseDouble(values[0]);
                            final double fullness = Double.parseDouble(values[1]);
                            view.update(temp,fullness, container.depth(), fullness <= container.trashThresh());
                        } catch (NumberFormatException ignored){

                        }
                    }
                }
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    throw new IllegalStateException(e);
                }
            }
        }).start();
    }
}

