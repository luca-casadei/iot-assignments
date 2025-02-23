#include <Arduino.h>
#include "devices/Potentiometer.hpp"

Potentiometer::Potentiometer(const int pin)
{
    pinMode(pin, INPUT);
}

int Potentiometer::getValue()
{
    return map(this->currentValue, 8, 1015, 1, 4);
}