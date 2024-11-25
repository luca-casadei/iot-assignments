#include <Arduino.h>
#include "components/TemperatureSensor.hpp"

TemperatureSensor::TemperatureSensor(unsigned int pin) : Component(pin) {
    pinMode(pin, INPUT);
}

double TemperatureSensor::getTemperature() {
    return (analogRead(this->getPin()) * 4.88) / 10;
}