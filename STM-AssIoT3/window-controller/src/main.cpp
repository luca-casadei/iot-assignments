#include <Arduino.h>
#include "kernel/Scheduler.hpp"
#include "model/HWPlatform.hpp"
#include "model/UserPanel.hpp"
#include "kernel/MsgService.hpp"
#include "model/Dashboard.hpp"
#include "tasks/AutomaticTask.hpp"
#include "tasks/ManualTask.hpp"

Scheduler sched;

HWPlatform *pHWPlatform;
UserPanel *pUserPanel;
Dashboard *pDashboard;

void setup()
{
    MsgService.init();
    sched.init(50);

    pHWPlatform = new HWPlatform();
    pHWPlatform->init();

    pUserPanel = new UserPanel(pHWPlatform);
    pUserPanel->init();

    pDashboard = new Dashboard(pUserPanel);
    pDashboard->init();

    Task *pBackendCommTask = new AutomaticTask(pDashboard, pUserPanel);
    pBackendCommTask->init(100);
    Task *pManualWindowTask = new ManualTask(pDashboard, pUserPanel);
    pManualWindowTask->init(100);
    pManualWindowTask->setActive(false);

    sched.addTask(pBackendCommTask);
    sched.addTask(pManualWindowTask);

    Serial.begin(9600);
}

void loop()
{
    sched.schedule();
}
