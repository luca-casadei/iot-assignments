#pragma once

class Potentiometer
{
public:
    Potentiometer();
    int getValue();

private:
    int currentValue;
};