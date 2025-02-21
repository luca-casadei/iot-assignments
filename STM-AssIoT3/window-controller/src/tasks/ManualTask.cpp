#include "tasks/ManualTask.hpp"
#include <Arduino.h>
#include "pins.hpp"

#define DISCHARGE_TIME 5000
#define OPENING_DISCHARGING_TIME 1000
#define CLOSING_DISCHARGING_TIME 1000

ManualTask::ManualTask(Dashboard* pDashboard, HWPlatform* pHWPlatform): 
    pDashboard(pDashboard), pHWPlatform(pHWPlatform){
    setState(CONTROLLING);
}
  
void ManualTask::tick(){
    pDashboard->sync();
    pDashboard->notifyNewState();
    switch (state){    
        case CONTROLLING:{
            break;
        }
    }
}

void ManualTask::setState(State s){
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long ManualTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool ManualTask::checkAndSetJustEntered(){
    bool bak = justEntered;
    if (justEntered){
      justEntered = false;
    }
    return bak;
}
