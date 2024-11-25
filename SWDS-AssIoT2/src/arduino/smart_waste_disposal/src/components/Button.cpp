#include <Arduino.h>
#include "components/Button.hpp"

void Button::init() {
    pinMode(this->getPin(), INPUT);
}

bool Button::isPressed() {
    bool currentState = digitalRead(this->getPin());

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