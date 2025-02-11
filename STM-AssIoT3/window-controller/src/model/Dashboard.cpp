#include "Dashboard.hpp"
#include <Arduino.h>
#include "kernel/MsgService.hpp"

Dashboard::Dashboard(){
}

void Dashboard::init(){
  maintenanceDoneNotified = false;
  dischargeCmdRequested = false;
}

void Dashboard::notifyNewState(){
  String st;
  // TODO: gestione 
  MsgService.sendMsg(String("cw:st:") + st);  
}

void Dashboard::sync(){
  if (MsgService.isMsgAvailable()){
    Msg* msg = MsgService.receiveMsg();
    if (msg != NULL){
      if (msg->getContent() == "ok"){
        maintenanceDoneNotified = true;
      } else if (msg->getContent() == "di"){
        dischargeCmdRequested = true;
      }
      delete msg;
    }  
  }
}

bool Dashboard::checkAndResetDischargeRequest(){
  bool com = this->dischargeCmdRequested;
  dischargeCmdRequested = false;
  return com;
}

bool Dashboard::checkAndResetMaintenanceDone(){
  bool com = this->maintenanceDoneNotified;
  maintenanceDoneNotified = false;
  return com;
}
