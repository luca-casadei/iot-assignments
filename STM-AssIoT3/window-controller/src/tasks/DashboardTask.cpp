#include "tasks/DashboardTask.hpp"
#include <Arduino.h>
#include "constants.hpp"
#include "kernel/MsgService.hpp"


DashboardTask::DashboardTask(UserPanel* pUserPanel, TaskWithState *pAutomaticTask, TaskWithState *pManualTask)
{
    pUserPanel = pUserPanel;
    pAutomaticTask = pAutomaticTask;
    pManualTask = pManualTask;
}

void DashboardTask::notifyNewState(String msg)
{
  MsgService.sendMsg(msg);
}

void DashboardTask::notifyWindowPercentage()
{
  MsgService.sendMsg(String("WINDOW:") + (char *)(pUserPanel->getWindowOpeningPercentage()));
}

void DashboardTask::tick()
{
  if (MsgService.isMsgAvailable())
  {
    Msg *msg = MsgService.receiveMsg();
    if (msg != NULL)
    {
      String receivedMsg = msg->getContent();


      int separatorIndex = receivedMsg.indexOf(':');

      String firstPart, // MODE, STATE, TEMPERATURE
       secondPart;
      if (separatorIndex != -1) { 
        firstPart = receivedMsg.substring(0, separatorIndex);
        secondPart = receivedMsg.substring(separatorIndex + 1);
        if (firstPart == "MODE") 
        {
          pUserPanel->setSystemMode(secondPart == "AUTOMATIC" ? AUTOMATIC : MANUAL);
        } else if (firstPart == "STATE") 
        {
          
        } else if (firstPart == "TEMPERATURE") 
        {

        }
      } else {
        // ERRORE
      }
      
      
      if (msg->getContent())
      delete msg;
    }
  }
}
