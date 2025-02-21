#pragma once

#include "kernel/Task.hpp"
#include "kernel/TaskWithState.hpp"
#include "model/UserPanel.hpp"

class DashboardTask : public Task
{
public:
    DashboardTask(UserPanel* pUserPanel, TaskWithState *pAutomaticTask, TaskWithState *pManualTask);
    void tick();
    void notifyNewState(String msg);
    void notifyWindowPercentage();
private:
    UserPanel     *pUserPanel;
    TaskWithState *pAutomaticTask;
    TaskWithState *pManualTask;
};