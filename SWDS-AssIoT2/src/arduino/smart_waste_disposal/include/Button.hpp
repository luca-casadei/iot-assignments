#ifndef BUTTON_HPP
#define BUTTON_HPP

class Button {
public:
    Button(int pin);
    void begin();
    bool wasPressed();

private:
    int pin;
    bool lastState;
    unsigned long lastDebounceTime;
    static const unsigned long debounceDelay = 50;
};

#endif