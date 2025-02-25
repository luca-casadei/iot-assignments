#pragma once

class Potentiometer
{
public:
    Potentiometer(const int pin);
    int getValue();
    void sync();

private:
    int currentValue;
    unsigned int pin;
};