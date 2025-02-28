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
    getUserPanel()->printToLine(3, "");
    
    switch (currentState)
    {
    case NORMAL:
    {
        if (firstTimeEntering())
        {
            getUserPanel()->printToLine(0, " MODE: AUTOMATIC");
            getUserPanel()->printToLine(1, " STATE: NORMAL");
            getUserPanel()->setWindowPosition(0);
            getUserPanel()->printToLine(2, ("WINDOW: " + String(getUserPanel()->getWindowOpeningPercentage())).c_str());
        }
        break;
    }
    case HOT:
    {
        float perc = 1 + ((getUserPanel()->getTemperature() - T1) / (T2 - T1)) * 99;
        getUserPanel()->setWindowPosition(perc);
        if (firstTimeEntering())
        {
            getUserPanel()->printToLine(0, " MODE: AUTOMATIC");
            getUserPanel()->printToLine(1, " STATE: HOT");
            getUserPanel()->printToLine(2, ("WINDOW: " + String(getUserPanel()->getWindowOpeningPercentage())).c_str());
        }
        break;
    }
    case TOO_HOT:
    {
        if (firstTimeEntering())
        {
            getUserPanel()->printToLine(0, " MODE: AUTOMATIC");
            getUserPanel()->printToLine(1, " STATE: TOO_HOT");
            getUserPanel()->setWindowPosition(100);
            getUserPanel()->printToLine(2, ("WINDOW: " + String(getUserPanel()->getWindowOpeningPercentage())).c_str());
        }
        break;
    }
    case ALARM:
    {
        if (firstTimeEntering())
        {
            getUserPanel()->printToLine(0, " MODE: AUTOMATIC");
            getUserPanel()->printToLine(1, " STATE: ALARM");
            getUserPanel()->setWindowPosition(100);
            getUserPanel()->printToLine(2, ("WINDOW: " + String(getUserPanel()->getWindowOpeningPercentage())).c_str());

        }
        break;
    }
    default:
    {
        if (firstTimeEntering()){
            getUserPanel()->printToLine(0, " MODE: AUTOMATIC");
            getUserPanel()->printToLine(1, " STATE: INVALID");
        }
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
