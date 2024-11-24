#pragma once

class Servo;

class ServoMotor
{
public:
    ServoMotor(unsigned int pin);
    virtual ~ServoMotor();
    virtual void open() final;
    virtual void close() final;
    virtual void empty() final;
    virtual void init() final;

private:
    Servo * servo_motor;
    unsigned int pin;
};