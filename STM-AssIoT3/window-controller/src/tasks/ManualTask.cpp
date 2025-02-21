#include "tasks/ManualTask.hpp"
#include <Arduino.h>
#include "constants.hpp"

#define DISCHARGE_TIME 5000
#define OPENING_DISCHARGING_TIME 1000
#define CLOSING_DISCHARGING_TIME 1000

ManualTask::ManualTask(Dashboard *pDashboard, UserPanel *pUserPanel) : pDashboard(pDashboard), pUserPanel(pUserPanel)
{
    setState(CONTROLLING);
}

void ManualTask::tick()
{
    String msg = "MANUAL:";
    pDashboard->sync();
    switch (state)
    {
    case CONTROLLING:
    {
        msg += "CONTROLLING";
        break;
    }
    }
    pDashboard->notifyNewState(msg);
}

void ManualTask::setState(State s)
{
    state = s;
    stateTimestamp = millis();
    justEntered = true;
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
