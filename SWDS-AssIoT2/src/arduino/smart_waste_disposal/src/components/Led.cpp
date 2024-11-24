#include <Arduino.h>
#include "components/Led.hpp"

Led::Led(int pin) {
  this->pin = pin;
}

void Led::init(){
  pinMode(pin, OUTPUT);
}

void Led::switchOn() {
  digitalWrite(pin,HIGH);
}

void Led::switchOff() {
  digitalWrite(pin,LOW);
};

Led::~Led(){};