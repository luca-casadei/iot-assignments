#include "components/MotionDetector.hpp"
#include <Arduino.h>

MotionDetector::MotionDetector(unsigned int pin) : Component(pin) { pinMode(this->getPin(), INPUT); }

bool MotionDetector::detected()
{
    return digitalRead(this->getPin()) == HIGH;
}