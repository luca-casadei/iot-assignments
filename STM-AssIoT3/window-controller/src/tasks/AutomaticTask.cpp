#include "tasks/AutomaticTask.hpp"
#include <Arduino.h>
#include "constants.hpp"

#define DISCHARGE_TIME 5000
#define OPENING_DISCHARGING_TIME 1000
#define CLOSING_DISCHARGING_TIME 1000

AutomaticTask::AutomaticTask(Dashboard *pDashboard, UserPanel *pUserPanel) : pDashboard(pDashboard), pUserPanel(pUserPanel)
{
    setState(NORMAL);
    pUserPanel->printToLine(0, "AUTOMATIC");
}

void AutomaticTask::tick()
{
    String msg = "AUTOMATIC:";
    pDashboard->sync();
    pUserPanel->printToLine(1, "TEMPERATURE ...");
    switch (state)
    {
    case NORMAL:
    {
        msg += "NORMAL";
        break;
    }
    case HOT:
    {
        msg += "HOT";
        break;
    }
    case TOO_HOT:
    {
        msg += "TOO_HOT";
        break;
    }
    case ALARM:
    {
        msg += "ALARM";
        break;
    }
    }
    pDashboard->notifyNewState(msg);
}

void AutomaticTask::setState(State s)
{
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long AutomaticTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

bool AutomaticTask::checkAndSetJustEntered()
{
    bool bak = justEntered;
    if (justEntered)
    {
        justEntered = false;
    }
    return bak;
}
