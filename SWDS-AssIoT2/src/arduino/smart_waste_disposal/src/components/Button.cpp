#include <Arduino.h>
#include "components/Button.hpp"

Button::Button(int pin) : pin(pin) {}

void Button::begin() {
    pinMode(pin, INPUT);
}

bool Button::wasPressed() {
    bool currentState = digitalRead(pin);

    if (currentState != lastState)
    {
        lastDebounceTime = millis();
    }

    // controllo se il tempo di debounce è trascorso
    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (currentState == LOW && lastState == HIGH)
        {
            lastState = currentState;
            return true;
        }
    }

    lastState = currentState;
    return false;
}