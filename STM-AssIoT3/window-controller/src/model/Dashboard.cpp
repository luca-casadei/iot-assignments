#include "./model/Dashboard.hpp"
#include <Arduino.h>
#include "kernel/MsgService.hpp"

Dashboard::Dashboard(UserPanel *pUserPanel)
{
  pUserPanel = pUserPanel;
}

void Dashboard::init()
{
}

void Dashboard::notifyNewState(String msg)
{
  MsgService.sendMsg(msg);
}

void Dashboard::notifyWindowPercentage()
{
  MsgService.sendMsg(String("WINDOW:") + (char *)(pUserPanel->getWindowOpeningPercentage()));
}

void Dashboard::sync()
{
  if (MsgService.isMsgAvailable())
  {
    Msg *msg = MsgService.receiveMsg();
    if (msg != NULL)
    {
      String receivedMsg = msg->getContent();
      int separatorIndex = receivedMsg.indexOf(':');

      String systemMode, innerMode;
      if (separatorIndex != -1) {
        systemMode = receivedMsg.substring(0, separatorIndex);
        innerMode = receivedMsg.substring(separatorIndex + 1);
      } else {
        systemMode = receivedMsg;
        innerMode = "";
      }
      pUserPanel->setSystemMode(systemMode == "AUTOMATIC" ? AUTOMATIC : MANUAL);
      
      if (msg->getContent())
      delete msg;
    }
  }
}
