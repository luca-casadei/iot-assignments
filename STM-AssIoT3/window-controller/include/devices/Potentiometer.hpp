#pragma once

class Potentiometer
{
public:
    Potentiometer(const int pin);
    int getValue();

private:
    int currentValue;
};