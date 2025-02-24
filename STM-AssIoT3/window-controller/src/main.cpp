#include <Arduino.h>
#include "kernel/Scheduler.hpp"
#include "model/UserPanel.hpp"
#include "kernel/MsgService.hpp"
#include "tasks/DashboardTask.hpp"
#include "tasks/AutomaticTask.hpp"
#include "tasks/ManualTask.hpp"

Scheduler sched;


void setup()
{
    
    MsgService.init();
    
    sched.init(50);
    
    UserPanel *pUserPanel = new UserPanel();
    pUserPanel->init();
    
    TaskWithState *pBackendCommTask = new AutomaticTask(pUserPanel);
    pBackendCommTask->init(100);
    pBackendCommTask->setActive(true);
    TaskWithState *pManualWindowTask = new ManualTask(pUserPanel);
    pManualWindowTask->init(100);
    pManualWindowTask->setActive(false);
    Task *pDashboardTask = new DashboardTask(pUserPanel, pBackendCommTask, pManualWindowTask);
    pDashboardTask->init(100);
    pDashboardTask->setActive(true);
    
    sched.addTask(pDashboardTask);
    sched.addTask(pBackendCommTask);
    sched.addTask(pManualWindowTask);
}

void loop()
{
    sched.schedule();
}
