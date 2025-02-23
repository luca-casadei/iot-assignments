#include "tasks/DashboardTask.hpp"
#include "constants.hpp"
#include "kernel/MsgService.hpp"

DashboardTask::DashboardTask(UserPanel* pUserPanel, TaskWithState *pAutomaticTask, TaskWithState *pManualTask)
{
  pUserPanel = pUserPanel;
  pAutomaticTask = pAutomaticTask;
  pManualTask = pManualTask;
}

void DashboardTask::notifyChangeMode()
{
  MsgService.sendMsg("MODE:CHANGE");
}

void DashboardTask::notifyWindowChange() {
  MsgService.sendMsg(String(this->pUserPanel->getWindowOpeningPercentage()));
}

void DashboardTask::tick()
{
  if (MsgService.isMsgAvailable())
  {
    Msg *msg = MsgService.receiveMsg();
    if (msg != NULL)
    {
      String receivedMsg = msg->getContent();

      int separatorIndex = receivedMsg.indexOf(MESSAGE_SEPARATOR);

      String firstPart, secondPart;
      
      if (separatorIndex != -1)
      {
        firstPart = receivedMsg.substring(0, separatorIndex);
        secondPart = receivedMsg.substring(separatorIndex + 1);

        
        if (firstPart.compareTo("MODE") == 0)
        {
          if (secondPart.compareTo("AUTOMATIC"))
          {
            this->pAutomaticTask->setActive(true);
            this->pManualTask->setActive(false);
          }
          else if (secondPart.compareTo("MANUAL"))
          {
            this->pAutomaticTask->setActive(false);
            this->pManualTask->setActive(true);
          }
        }
        else if (firstPart == "STATE")
        {
          if (this->pAutomaticTask->isActive())
          {
            this->pAutomaticTask->changeState(this->pAutomaticTask->getStateFromString(secondPart));
          }
          else if (this->pManualTask->isActive())
          {
            this->pManualTask->changeState(this->pManualTask->getStateFromString(secondPart));
          }
        }
        else if (firstPart.compareTo("TEMPERATURE") == 0)
        {
          this->pUserPanel->saveTemperature((float)atof(secondPart.c_str()));
        }
      }
      else
      {
        // ERRORE
      }

      if (msg->getContent())
      {
        delete msg;
      }
    }
  }
  if (this->pUserPanel->isButtonModePressed())
  {
    this->notifyChangeMode();
  }
}
