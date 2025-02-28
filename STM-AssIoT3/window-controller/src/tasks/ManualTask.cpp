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
    this->getUserPanel()->sync();
    switch (currentState)
    {
    case CONTROLLING:
    {
        if (getUserPanel()->getDashboardPercentage() != -1){
            getUserPanel()->setOldPotValue(getUserPanel()->getPotentiometerValue());
            this->getUserPanel()->setWindowPosition(getUserPanel()->getDashboardPercentage());
        }
        else if (abs(this->getUserPanel()->getPotentiometerValue() - this->getUserPanel()->getOldPotValue()) > POT_CHANGE_MARGIN)
        {
            this->getUserPanel()->setDashboardPercentage(-1);
            this->getUserPanel()->setWindowPosition(getUserPanel()->getPotentiometerValue());
        }
        if (firstTimeEntering())
        {
            getUserPanel()->printToLine(0, " MODE: MANUAL");
            getUserPanel()->printToLine(1, " STATE: CONTROLLING");
            getUserPanel()->printToLine(2, ("WINDOW: " + String(getUserPanel()->getWindowOpeningPercentage())).c_str());
            getUserPanel()->printToLine(3, ("TEMPERATURE: " + String(getUserPanel()->getTemperature())).c_str());
        }
        break;
    }
    default:
    {
        if (firstTimeEntering()){
            getUserPanel()->printToLine(0, "MANUAL - INVALID");
        }
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
