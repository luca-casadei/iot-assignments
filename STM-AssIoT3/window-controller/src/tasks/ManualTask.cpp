#include "tasks/ManualTask.hpp"
#include <Arduino.h>
#include "constants.hpp"

ManualTask::ManualTask(UserPanel *pUserPanel)
{
    this->setUserPanel(pUserPanel);
    changeState(CONTROLLING);
}

void ManualTask::tick()
{
    
    switch (currentState)
    {
    case CONTROLLING:
    {
        if (firstTimeEntering())
        {
            pUserPanel->printToLine(1, "MANUAL - CONTROLLING");
        }
        break;
    }
    default:
    {
        pUserPanel->printToLine(1, "MANUAL - INVALID");
    }
    }
}

void ManualTask::changeState(State s)
{
    if (s == CONTROLLING)
    {
        currentState = s;
        justEntered = false;
    }
}
