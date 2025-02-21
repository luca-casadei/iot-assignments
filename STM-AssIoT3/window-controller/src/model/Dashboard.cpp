#include "./model/Dashboard.hpp"
#include <Arduino.h>
#include "kernel/MsgService.hpp"

Dashboard::Dashboard(){
}

void Dashboard::init(){
  actualState = AUTOMATIC;
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
      if (msg->getContent() == "AUTOMATIC"){
        actualState = AUTOMATIC;
      } else if (msg->getContent() == "MANUAL"){
        actualState = MANUAL;
      }
      delete msg;
    }  
  }
}

