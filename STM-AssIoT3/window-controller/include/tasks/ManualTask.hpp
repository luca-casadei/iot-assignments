#pragma once

#include "kernel/TaskWithState.hpp"
#include "model/UserPanel.hpp"

class ManualTask : public TaskWithState
{

public:
    ManualTask();
    void tick();
    void changeState(State newState);

private:
    long elapsedTimeInState();
    bool checkAndSetJustEntered();

    UserPanel *pUserPanel;
};