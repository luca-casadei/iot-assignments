#include <Arduino.h>
#include "devices/Potentiometer.hpp"

Potentiometer::Potentiometer(const int pin)
{
    pinMode(pin, INPUT);
    this->pin = pin;
}

int Potentiometer::getValue()
{
    return map(constrain(this->currentValue, 8, 1015), 8, 1015, 1, 99);
}

void Potentiometer::sync(){
    this->currentValue = analogRead(this->pin);
}