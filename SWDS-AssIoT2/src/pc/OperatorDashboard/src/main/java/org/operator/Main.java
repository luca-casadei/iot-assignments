package org.operator;

import org.operator.controller.SensorController;
import org.operator.model.Container;
import org.operator.view.SensorView;

public final class Main {
    private static final double DEPTH = 50;
    private static final double TRASH_THRESH = 5;
    public static void main(String[] args) {
        final SensorController controller = new SensorController(new Container(DEPTH, TRASH_THRESH), new SensorView());
        controller.startUpdatingView();
    }
}