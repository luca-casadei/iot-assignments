#pragma once

#include "Component.hpp"

class MotionDetector : public Component
{
public:
    MotionDetector(unsigned int pin);
    bool detected();
};