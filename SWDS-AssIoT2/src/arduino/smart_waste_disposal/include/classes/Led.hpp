#pragma once
#include "interfaces/ILed.hpp"

class Led : public ILed
{
public:
    Led(int pin);
    virtual ~Led();
    void switchOn() final;
    void switchOff() final;
    void init() final;
private:
    unsigned int pin;
};
