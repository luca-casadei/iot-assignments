#include "tasks/ManualTask.hpp"
#include <Arduino.h>
#include "constants.hpp"

#define DISCHARGE_TIME 5000
#define OPENING_DISCHARGING_TIME 1000
#define CLOSING_DISCHARGING_TIME 1000

ManualTask::ManualTask()
{
    changeState(CONTROLLING);
}

void ManualTask::tick()
{
    switch (currentState)
    {
    case CONTROLLING:
    {
        break;
    }
    default:{
        
    }
    }
}

void ManualTask::changeState(State s)
{
    if (s == CONTROLLING)
    {
        currentState = s;
        stateTimestamp = millis();
        justEntered = true;
    }
}

long ManualTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

bool ManualTask::checkAndSetJustEntered()
{
    bool bak = justEntered;
    if (justEntered)
    {
        justEntered = false;
    }
    return bak;
}
