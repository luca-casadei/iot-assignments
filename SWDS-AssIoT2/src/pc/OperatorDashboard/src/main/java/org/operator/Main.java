package org.operator;

import org.operator.controller.SensorController;
import org.operator.model.Container;
import org.operator.view.SensorView;

/**
 * IoT Assignment N.2
 * Luca Casadei
 * Francesco Pazzaglia
 * Mattia Morri
 */
public final class Main {
    private static final double TRASH_THRESH = 3;

    public static void main(final String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java -jar <jar_file> <depth_in_centimeters>");
        } else {
            try {
                final double depth = Double.parseDouble(args[0]);
                final SensorController controller = new SensorController(new Container(depth, TRASH_THRESH), new SensorView());
                controller.startUpdatingView();
            } catch (NumberFormatException e) {
                System.out.println("Invalid depth in centimeters: " + args[0]);
            }
        }
    }
}