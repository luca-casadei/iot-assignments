package org.operator.components;

public final class LiquidContainer {
    private int level;

    public LiquidContainer(int initialLevel) {
        this.level = Math.max(0, Math.min(100, initialLevel));
    }

    public int getLevel() {
        return level;
    }

    public void decreaseLevel(int amount) {
        level = Math.max(0, level - amount);
    }

    public void increaseLevel(int amount) {
        level = Math.min(100, level + amount);
    }

    public void setLevel(int level) {
        this.level = Math.max(0, Math.min(100, level));
    }
}
