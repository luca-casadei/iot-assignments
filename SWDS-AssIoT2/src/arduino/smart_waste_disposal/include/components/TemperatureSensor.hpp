#pragma once

#include "Component.hpp"

class TemperatureSensor : public Component
{
public:
    TemperatureSensor(unsigned int pin);
    double getTemperature();
};