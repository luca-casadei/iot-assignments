#include <Arduino.h>
#include "kernel/Scheduler.hpp"
#include "model/HWPlatform.hpp"
#include "model/UserPanel.hpp"
#include "kernel/MsgService.hpp"
#include "model/Dashboard.hpp"
#include "tasks/AutomaticTask.hpp"


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

    Task* pBackendCommTask = new AutomaticTask(pDashboard);
    pBackendCommTask->init(100);

    Serial.begin(9600);
}

void loop() {
    if(MsgService.isMsgAvailable()){
        Msg * messaggio = MsgService.receiveMsg();
        MsgService.sendMsg(messaggio->getContent());
        delete messaggio;
    }
    else{
        MsgService.sendMsg("Ciao!");
    }
    delay(2000);
}
