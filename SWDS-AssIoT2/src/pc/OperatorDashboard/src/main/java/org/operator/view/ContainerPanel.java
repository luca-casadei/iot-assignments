package org.operator.view;

import org.operator.components.LiquidContainer;

import javax.swing.JPanel;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Color;


public class ContainerPanel extends JPanel {
    private final LiquidContainer container;

    public ContainerPanel (LiquidContainer container) {
        this.container = container;
        setPreferredSize(new Dimension(200, 400));
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        int width = getWidth();
        int height = getHeight();

        int containerWidth = (int) (width * 0.8);
        int containerHeight = (int) (height * 0.9);
        int containerX = (width - containerWidth) / 2;
        int containerY = (height - containerHeight) / 2;

        g.setColor(Color.BLACK);
        g.drawRect(containerX, containerY, containerWidth, containerHeight);

        int liquidHeight = (int) (container.getLevel() * (containerHeight / 100.0));
        g.setColor(Color.orange);
        g.fillRect(containerX + 1, containerY + containerHeight - liquidHeight, containerWidth - 1, liquidHeight);
    }
}
