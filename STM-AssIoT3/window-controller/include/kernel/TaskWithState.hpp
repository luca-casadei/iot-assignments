#pragma once

#include <string.h>
#include "Task.hpp"

class String;

enum State
{
    NORMAL,
    HOT,
    TOO_HOT,
    ALARM,
    CONTROLLING,
    INVALID
};

class TaskWithState : public Task
{
public:
    virtual ~TaskWithState() {};
    virtual void changeState(State newState) = 0;
    State getStateFromString(String stateString);

    bool firstTimeEntering();

protected:
    State currentState;
    unsigned long stateTimestamp;
    bool justEntered = false;
    
};
