#pragma once
class Led
{
public:
    Led(int pin);
    virtual ~Led();
    virtual void switchOn() final;
    virtual void switchOff() final;
    virtual void init() final;
private:
    unsigned int pin;
};
