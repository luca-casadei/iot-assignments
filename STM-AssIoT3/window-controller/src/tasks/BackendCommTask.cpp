#include "tasks/BackendCommTask.hpp"
#include <Arduino.h>
#include "pins.hpp"

#define DISCHARGE_TIME 5000
#define OPENING_DISCHARGING_TIME 1000
#define CLOSING_DISCHARGING_TIME 1000

BackendCommTask::BackendCommTask(Dashboard* pDashboard): 
    pDashboard(pDashboard){
    setState(NORMAL);
}
  
void BackendCommTask::tick(){
    pDashboard->sync();
    pDashboard->notifyNewState();
    switch (state){    
        case NORMAL: {

            break;
        }
        case HOT: {

            break;
        }
        case TOO_HOT: {

            break;
        }
        case ALARM: {

            break;
        }
    }
}

void BackendCommTask::setState(State s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long BackendCommTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool BackendCommTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}
