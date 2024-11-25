#pragma once

class Component
{
protected:
    Component(unsigned int pin);

public:
    unsigned int getPin();

private:
    unsigned int pin;
};