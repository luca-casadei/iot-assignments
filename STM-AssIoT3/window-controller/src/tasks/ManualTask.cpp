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
            getUserPanel()->printToLine(1, "MANUAL - CONTROLLING");
        }
        if (getUserPanel()->getDashboardPercentage() != -1){
            getUserPanel()->setOldPotValue(getUserPanel()->getPotentiometerValue());
            this->getUserPanel()->setWindowPosition(getUserPanel()->getDashboardPercentage());
        }
        else if (abs(this->getUserPanel()->getPotentiometerValue() - this->getUserPanel()->getOldPotValue()) > POT_CHANGE_MARGIN)
        {
            this->getUserPanel()->setDashboardPercentage(-1);
            this->getUserPanel()->setWindowPosition(getUserPanel()->getPotentiometerValue());
        }
        break;
    }
    default:
    {
        if (firstTimeEntering()){
            getUserPanel()->printToLine(1, "MANUAL - INVALID");
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
