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
        if (this->getUserPanel()->getPotentiometerValue() != this->getUserPanel()->getWindowOpeningPercentage())
        {
            this->getUserPanel()->setWindowPosition(this->getUserPanel()->getPotentiometerValue());
        }
        break;
    }
    default:
    {
        getUserPanel()->printToLine(1, "MANUAL - INVALID");
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
