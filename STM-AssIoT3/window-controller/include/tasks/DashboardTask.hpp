#pragma once

#include "kernel/Task.hpp"
#include "kernel/TaskWithState.hpp"
#include "model/UserPanel.hpp"

#define MESSAGE_SEPARATOR ':'

class DashboardTask : public Task
{
public:
    DashboardTask(UserPanel *pUserPanel, TaskWithState *pAutomaticTask, TaskWithState *pManualTask);
    void tick();

private:
    UserPanel *pUserPanel;
    TaskWithState *pAutomaticTask;
    TaskWithState *pManualTask;
    void notifyChangeMode();
    void notifyWindowChange();
};