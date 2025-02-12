#include "tasks/AutomaticTask.hpp"
#include <Arduino.h>
#include "pins.hpp"

#define DISCHARGE_TIME 5000
#define OPENING_DISCHARGING_TIME 1000
#define CLOSING_DISCHARGING_TIME 1000

AutomaticTask::AutomaticTask(Dashboard* pDashboard): 
    pDashboard(pDashboard){
    setState(NORMAL);
}
  
void AutomaticTask::tick(){
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

void AutomaticTask::setState(State s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long AutomaticTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool AutomaticTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}
