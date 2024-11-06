#include <Servo.h>
#include "ServoMotor.hpp"

ServoMotor::ServoMotor(unsigned int pin) {
    this->servo_motor->attach(pin);
}

ServoMotor::~ServoMotor() {
    this->servo_motor->detach();
    delete this->servo_motor;
}

void ServoMotor::open() {
    this->servo_motor->write(90);
}

void ServoMotor::close() {
    this->servo_motor->write(0);
}

void ServoMotor::empty() {
    this->servo_motor->write(-90);
}