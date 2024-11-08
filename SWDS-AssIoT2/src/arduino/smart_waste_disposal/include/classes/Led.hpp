#pragma once
#include "interfaces/ILed.hpp"

class Led : public ILed
{
public:
    Led(int pin);
    void switchOn() final;
    void switchOff() final;
    void init() final;
private:
    byte pin;
};
