#include "classes/ServoMotor.hpp"
#include <Arduino.h>

#define OPEN 0
#define CLOSED 90
#define EMPTY 180

ServoMotor::ServoMotor(uint8_t pin) {
    this->servo_motor = Servo();
    this->pin = pin;
}

ServoMotor::~ServoMotor() {
    this->servo_motor.detach();
}

void ServoMotor::init(){
    this->servo_motor.attach(this->pin);
}

void ServoMotor::open() {
    this->servo_motor.write(OPEN);
}

void ServoMotor::close() {
    this->servo_motor.write(CLOSED);
}

void ServoMotor::empty() {
    this->servo_motor.write(EMPTY);
}