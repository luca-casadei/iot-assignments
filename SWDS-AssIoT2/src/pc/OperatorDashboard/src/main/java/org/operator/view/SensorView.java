package org.operator.view;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.SwingUtilities;
import javax.swing.border.CompoundBorder;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Toolkit;
import java.awt.event.ActionListener;

public final class SensorView extends JFrame {
    private final JLabel temperatureLabel;
    private final JLabel distanceLabel;
    private final JButton emptyButton;
    private final JButton restoreButton;
    private final JProgressBar fullnessBar;
    private final JLabel fullLabel;

    public SensorView() {
        final Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
        setTitle("DashBoard Operatore");
        setSize((int)d.getWidth() / 4, (int)d.getHeight() / 2);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        temperatureLabel = new JLabel("Temperatura: -- °C");
        distanceLabel = new JLabel("Spazio vuoto: -- cm");

        emptyButton = new JButton("EMPTY");
        restoreButton = new JButton("RESTORE");
        final JPanel contentPane = new JPanel(new BorderLayout());
        contentPane.setBorder(new CompoundBorder(
                BorderFactory.createEmptyBorder(50,50,50,50),
                BorderFactory.createLineBorder(Color.BLACK)
        ));

        final JPanel labelPanel = new JPanel(new FlowLayout());
        labelPanel.add(temperatureLabel);
        labelPanel.add(distanceLabel);
        contentPane.add(labelPanel, BorderLayout.NORTH);

        final JPanel buttonPanel = new JPanel();
        buttonPanel.add(emptyButton);
        buttonPanel.add(restoreButton);
        contentPane.add(buttonPanel, BorderLayout.SOUTH);

        this.fullnessBar = new JProgressBar(JProgressBar.VERTICAL,0,100);
        fullnessBar.setStringPainted(true);
        fullnessBar.setForeground(Color.BLUE);
        contentPane.add(fullnessBar, BorderLayout.CENTER);

        this.fullLabel = new JLabel("PIENO!");
        fullLabel.setForeground(Color.RED);
        fullLabel.setVisible(false);
        buttonPanel.add(fullLabel);

        setContentPane(contentPane);
    }

    public void update(final double temperature, final double fullness, final double depth, final boolean full) {
        SwingUtilities.invokeLater(() -> {
            temperatureLabel.setText("Temperatura: " + temperature + " °C");
            distanceLabel.setText("Spazio vuoto: " + fullness + " cm");
            fullnessBar.setMaximum((int)(depth * 100));
            fullnessBar.setValue((int)((depth - fullness) * 100));
            fullLabel.setVisible(full);
        });
    }

    public void addEmptyButtonListener(final ActionListener listener) {
        emptyButton.addActionListener(listener);
    }

    public void addRestoreButtonListener(final ActionListener listener) {
        restoreButton.addActionListener(listener);
    }
}
