#include "tasks/AutomaticTask.hpp"
#include <Arduino.h>
#include "constants.hpp"

#define DISCHARGE_TIME 5000
#define OPENING_DISCHARGING_TIME 1000
#define CLOSING_DISCHARGING_TIME 1000

AutomaticTask::AutomaticTask()
{
    changeState(NORMAL);

}

void AutomaticTask::tick()
{
    switch (currentState)
    {
    case NORMAL:
    {
        break;
    }
    case HOT:
    {
        break;
    }
    case TOO_HOT:
    {
        break;
    }
    case ALARM:
    {
        break;
    }
    }
}

void AutomaticTask::changeState(State newState)
{
    if (newState != CONTROLLING){
        currentState = newState;
        stateTimestamp = millis();
        justEntered = true;
    }
}

long AutomaticTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

bool AutomaticTask::checkAndSetJustEntered()
{
    bool bak = justEntered;
    if (justEntered)
    {
        justEntered = false;
    }
    return bak;
}


