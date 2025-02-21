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

void Dashboard::notifyNewState()
{
  MsgService.sendMsg(String("MODE:") + pUserPanel->selectedMode());
}

void Dashboard::notifyWindowOpening() 
{
  MsgService.sendMsg(String("WINDOW:") + (String)(pUserPanel->getWindowOpeningPercentage()));
}

void Dashboard::sync()
{
  if (MsgService.isMsgAvailable())
  {
    Msg *msg = MsgService.receiveMsg();
    if (msg != NULL)
    {
      /*if (msg->getContent() == "AUTOMATIC")
      {
        actualState = AUTOMATIC;
      }
      else if (msg->getContent() == "MANUAL")
      {
        actualState = MANUAL;
      }*/
      delete msg;
    }
  }
}
