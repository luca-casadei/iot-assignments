#include <Arduino.h>
#include "components/Button.hpp"

Button::Button(unsigned int pin): Component(pin) {}

void Button::init() {
    pinMode(this->getPin(), INPUT);
}

bool Button::isPressed() {
    return digitalRead(this->getPin());
}