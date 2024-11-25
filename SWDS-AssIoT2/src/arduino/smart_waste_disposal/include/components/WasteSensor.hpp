#pragma once

#include "Component.hpp"

class WasteSensor : public Component
{
public:
    WasteSensor(unsigned int echo_pin, unsigned int trig_pin);
    void init();
    double getWasteLevel(double temperature);

private:
    unsigned int echo_pin;
};