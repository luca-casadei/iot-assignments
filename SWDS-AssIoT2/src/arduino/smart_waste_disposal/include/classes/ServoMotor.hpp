#pragma once
#include <Servo.h>
#include "interfaces/IServoMotor.hpp"

class ServoMotor : public IServoMotor
{
public:
    ServoMotor(uint8_t pin);
    ~ServoMotor();
    void open() final;
    void close() final;
    void empty() final;
    void init() final;

protected:
    Servo servo_motor;
    uint8_t pin;
};