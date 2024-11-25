#pragma once

#include "Component.hpp"

class Button : public Component
{
public:
    Button(unsigned int pin);
    void init();
    bool isPressed();

private:
    bool lastState;
    unsigned long lastDebounceTime;
    static const unsigned long debounceDelay = 50;
};