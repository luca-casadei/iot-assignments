#pragma once

#include "kernel/Task.hpp"
#include "model/Dashboard.hpp"

class ManualTask : public Task
{

public:
    ManualTask(Dashboard *pDashboard, UserPanel *pUserPanel);
    void tick();

private:
    enum State
    {
        CONTROLLING
    };
    void setState(State state);
    long elapsedTimeInState();
    void log(const String &msg);
    State state;

    bool checkAndSetJustEntered();

    long stateTimestamp;
    bool justEntered;

    Dashboard *pDashboard;
    UserPanel *pUserPanel;
};