#include <Arduino.h>
#include "kernel/Scheduler.hpp"
#include "model/HWPlatform.hpp"
#include "model/UserPanel.hpp"
#include "kernel/MsgService.hpp"
#include "model/Dashboard.hpp"
#include "tasks/BackendCommTask.hpp"


Scheduler sched;

HWPlatform* pHWPlatform;
UserPanel* pUserPanel;
Dashboard* pDashboard; 

void setup() {
    MsgService.init();
    sched.init(100);

    pHWPlatform = new HWPlatform();
    pHWPlatform->init();

    pUserPanel = new UserPanel(pHWPlatform);
    pUserPanel->init();

    pDashboard = new Dashboard();
    pDashboard->init();

    Task* pBackendCommTask = new BackendCommTask(pDashboard);
    pBackendCommTask->init(100);

}

void loop() {
}
