#include <Arduino.h>
#include "kernel/Scheduler.hpp"
#include "model/HWPlatform.hpp"
#include "model/UserPanel.hpp"
#include "kernel/MsgService.hpp"
#include "tasks/DashboardTask.hpp"
#include "tasks/AutomaticTask.hpp"
#include "tasks/ManualTask.hpp"

Scheduler sched;

HWPlatform *pHWPlatform;
UserPanel *pUserPanel;

void setup()
{

    MsgService.init();

    sched.init(150);
    pHWPlatform = new HWPlatform();
    pHWPlatform->init();

    pUserPanel = new UserPanel(pHWPlatform);
    pUserPanel->init();
    
    TaskWithState *pBackendCommTask = new AutomaticTask(pUserPanel);
    pBackendCommTask->init(300);
    pBackendCommTask->setActive(true);
    TaskWithState *pManualWindowTask = new ManualTask(pUserPanel);
    pManualWindowTask->init(300);
    pManualWindowTask->setActive(false);
    Task *pDashboardTask = new DashboardTask(pUserPanel, pBackendCommTask, pManualWindowTask);
    pDashboardTask->init(300);
    pDashboardTask->setActive(true);
    
    sched.addTask(pDashboardTask);
    sched.addTask(pBackendCommTask);
    sched.addTask(pManualWindowTask);
}

void loop()
{
    sched.schedule();
}
