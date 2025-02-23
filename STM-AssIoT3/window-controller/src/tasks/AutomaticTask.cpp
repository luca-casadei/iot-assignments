#include "tasks/AutomaticTask.hpp"
#include <Arduino.h>
#include "constants.hpp"

AutomaticTask::AutomaticTask(UserPanel *pUserPanel)
{
    this->setUserPanel(pUserPanel);
    changeState(NORMAL);
}

void AutomaticTask::tick()
{
    switch (currentState)
    {
    case NORMAL:
    {
        if (firstTimeEntering())
        {
            pUserPanel->printToLine(1, "AUTOMATIC - NORMAL");
        }
        break;
    }
    case HOT:
    {
        if (firstTimeEntering())
        {
            pUserPanel->printToLine(1, "AUTOMATIC - HOT");
        }
        break;
    }
    case TOO_HOT:
    {
        if (firstTimeEntering())
        {
            pUserPanel->printToLine(1, "AUTOMATIC - TOO_HOT");
        }
        break;
    }
    case ALARM:
    {
        if (firstTimeEntering())
        {
            pUserPanel->printToLine(1, "AUTOMATIC - ALARM");
        }
        break;
    }
    default:
    {
        pUserPanel->printToLine(1, "AUTOMATIC - INVALID");
        break;
    }
    }
}

void AutomaticTask::changeState(State newState)
{
    if (newState != CONTROLLING){
        currentState = newState;
        justEntered = false;
    }
}
