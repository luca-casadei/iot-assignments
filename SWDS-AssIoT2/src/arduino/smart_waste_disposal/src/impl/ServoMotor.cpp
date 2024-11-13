#include <Servo.h>
#include "classes/ServoMotor.hpp"

#define OPEN 0
#define CLOSED 90
#define EMPTY 180

ServoMotor::ServoMotor(unsigned int pin) {
    this->servo_motor = new Servo();
    this->pin = pin;
}

ServoMotor::~ServoMotor() {
    this->servo_motor->detach();
}

void ServoMotor::init(){
    this->servo_motor->attach(this->pin);
}

void ServoMotor::open() {
    this->servo_motor->write(OPEN);
}

void ServoMotor::close() {
    this->servo_motor->write(CLOSED);
}

void ServoMotor::empty() {
    this->servo_motor->write(EMPTY);
}