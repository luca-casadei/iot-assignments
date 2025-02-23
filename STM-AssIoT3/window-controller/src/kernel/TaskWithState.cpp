#include "kernel/TaskWithState.hpp"
#include <Arduino.h>

State TaskWithState::getStateFromString(String stateString)
{
    if (stateString.compareTo("NORMAL") == 0)
    {
        return NORMAL;
    }
    if (stateString.compareTo("HOT") == 0)
    {
        return HOT;
    }
    if (stateString.compareTo("TOO_HOT") == 0)
    {
        return TOO_HOT;
    }
    if (stateString.compareTo("ALARM") == 0)
    {
        return ALARM;
    }
    if (stateString.compareTo("CONTROLLING") == 0)
    {
        return CONTROLLING;
    }
    return INVALID;
}

bool TaskWithState::firstTimeEntering()
{
    if (!this->justEntered)
    {
        this->justEntered = true;
        return true;
    }
    else
    {
        return false;
    }
}