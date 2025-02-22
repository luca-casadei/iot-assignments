#pragma once

#include "kernel/TaskWithState.hpp"
#include "kernel/TaskWithUserPanel.hpp"

class ManualTask : public TaskWithState, public TaskWithUserPanel
{

public:
    ManualTask(UserPanel *pUserPanel);
    void tick();
    void changeState(State newState);
};