#include "components/WasteSensor.hpp"
#include <Arduino.h>

WasteSensor::WasteSensor(unsigned int echo_pin, unsigned int trig_pin) : Component(trig_pin){
    this->echo_pin = echo_pin;
}

void WasteSensor::init(){
    pinMode(this->echo_pin, INPUT);
    pinMode(this->getPin(), OUTPUT); // Trigger pin
}

double WasteSensor::getWasteLevel(double temperature){
    const double VS = 331.45 + 0.62 * temperature;
    digitalWrite(this->getPin(), LOW);
    digitalWrite(this->getPin(), HIGH);
    digitalWrite(this->getPin(), LOW);

    double timeUS = pulseIn(this->echo_pin, HIGH);
    double time = timeUS / 1000.0 / 1000.0 / 2;
    double distance = time * VS;
    return distance;
}