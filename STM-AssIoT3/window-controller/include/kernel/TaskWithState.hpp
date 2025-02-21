#pragma once

#include "Task.hpp"

class TaskWithState : public Task
{
protected:
    enum State
    {
        NORMAL,
        HOT,
        TOO_HOT,
        ALARM,
        CONTROLLING
    };
    State currentState;
    unsigned long stateTimestamp;
    bool justEntered;

public:
    virtual ~TaskWithState() { };
    virtual void changeState(State newState) = 0;
};
