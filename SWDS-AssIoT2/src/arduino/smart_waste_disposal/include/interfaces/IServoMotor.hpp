#pragma once

class IServoMotor{
    public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void empty() = 0;
    virtual void init() = 0;
};