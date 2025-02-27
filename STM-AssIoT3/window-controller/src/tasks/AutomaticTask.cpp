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
    this->getUserPanel()->sync();
    
    switch (currentState)
    {
    case NORMAL:
    {
        if (firstTimeEntering())
        {
            getUserPanel()->printToLine(1, "AUTOMATIC - NORMAL");
            getUserPanel()->setWindowPosition(0);
        }
        break;
    }
    case HOT:
    {
        if (firstTimeEntering())
        {
            getUserPanel()->printToLine(1, "AUTOMATIC - HOT");
        }
        float perc = 1 + ((getUserPanel()->getTemperature() - T1) / (T2 - T1)) * 99;
        getUserPanel()->setWindowPosition(perc);
        break;
    }
    case TOO_HOT:
    {
        if (firstTimeEntering())
        {
            getUserPanel()->printToLine(1, "AUTOMATIC - TOO_HOT");
            getUserPanel()->setWindowPosition(100);
        }
        break;
    }
    case ALARM:
    {
        if (firstTimeEntering())
        {
            getUserPanel()->printToLine(1, "AUTOMATIC - ALARM");
            getUserPanel()->setWindowPosition(100);
        }
        break;
    }
    default:
    {
        getUserPanel()->printToLine(1, "AUTOMATIC - INVALID");
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
