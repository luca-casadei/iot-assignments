#include "tasks/AutomaticTask.hpp"
#include <Arduino.h>
#include "constants.hpp"

#define DISCHARGE_TIME 5000
#define OPENING_DISCHARGING_TIME 1000
#define CLOSING_DISCHARGING_TIME 1000

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
            pUserPanel->setWindowPosition(0);
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
