#pragma once
#include "components/interfaces/IServoMotor.hpp"

class Servo;

class ServoMotor : public IServoMotor
{
public:
    ServoMotor(unsigned int pin);
    virtual ~ServoMotor();
    void open() final;
    void close() final;
    void empty() final;
    void init() final;

private:
    Servo * servo_motor;
    unsigned int pin;
};