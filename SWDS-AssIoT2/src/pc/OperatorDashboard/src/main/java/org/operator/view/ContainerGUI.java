package org.operator.view;

import org.operator.components.LiquidContainer;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.Timer;
import javax.swing.JButton;
import javax.swing.SwingConstants;
import java.awt.Font;
import java.awt.BorderLayout;
import javax.swing.JPanel;
import java.awt.FlowLayout;

public class ContainerGUI extends JFrame {
    private final LiquidContainer container;
    private final JLabel lblPercentage;
    private Timer timer;
    private final ContainerPanel containerPanel;

    public ContainerGUI() {

        setTitle("Container Simulation");
        setSize(400, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setResizable(true);

        container = new LiquidContainer(100);

        lblPercentage = new JLabel(container.getLevel() + "%", SwingConstants.CENTER);
        lblPercentage.setFont(new Font("Arial", Font.BOLD, 16));

        containerPanel = new ContainerPanel(container);

        final JButton btnEmpty = new JButton("Empty the container");
        final JButton btnRestore = new JButton("Restore the container");

        /*
        btnEmpty.addActionListener(e -> startEmptying());
        btnRestore.addActionListener(e -> restoreContainer());
         */

        final JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));
        buttonPanel.add(btnEmpty);
        buttonPanel.add(btnRestore);

        setLayout(new BorderLayout());
        add(lblPercentage, BorderLayout.NORTH);
        add(containerPanel, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);

        /*
        timer = new Timer(100, event -> {
            if (container.getLevel() > 0) {
                container.decreaseLevel(2);
                updateUI();
            } else {
                timer.stop();
            }
        });
         */
    }

    /*
    private void startEmptying() {
        if (!timer.isRunning()) {
            timer.start();
        }
    }
*/

    /*
    private void restoreContainer() {
        if (timer.isRunning()) {
            timer.stop();
        }
        container.increaseLevel(100);
        updateUI();
    }
     */

    /*
    private void updateUI() {
        containerPanel.repaint();
        lblPercentage.setText(container.getLevel() + "%");
    }
     */
}
