#include "tasks/DashboardTask.hpp"
#include "constants.hpp"
#include "kernel/MsgService.hpp"

DashboardTask::DashboardTask(UserPanel* pUserPanel, TaskWithState *pAutomaticTask, TaskWithState *pManualTask)
{
  this->pUserPanel = pUserPanel;
  this->pAutomaticTask = pAutomaticTask;
  this->pManualTask = pManualTask;
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
  this->pUserPanel->sync();

  if (MsgService.isMsgAvailable())
  {
    Msg *msg = MsgService.receiveMsg();
    if (msg != NULL)
    {
      String receivedMsg = msg->getContent();
      receivedMsg.trim();
      
      int firstSeparatorIndex = receivedMsg.indexOf(MESSAGE_SEPARATOR);
      int middleSeparatorIndex = receivedMsg.indexOf(MESSAGE_SEPARATOR, firstSeparatorIndex + 1);
      int lastSeparatorIndex = receivedMsg.lastIndexOf(MESSAGE_SEPARATOR);

      String temperature, state, mode, opening;
      
      if (firstSeparatorIndex != -1 && lastSeparatorIndex != -1 && middleSeparatorIndex != -1)
      {
        temperature = receivedMsg.substring(0, firstSeparatorIndex);
        state = receivedMsg.substring(firstSeparatorIndex + 1,middleSeparatorIndex);
        mode = receivedMsg.substring(middleSeparatorIndex + 1, lastSeparatorIndex);
        opening = receivedMsg.substring(lastSeparatorIndex + 1);

        pUserPanel->setDashboardPercentage(atoi(opening.c_str()));
        
        if (mode.compareTo("AUTOMATIC") == 0)
        {
          this->pAutomaticTask->setActive(true);
          this->pManualTask->setActive(false);
        }
        else if (mode.compareTo("MANUAL") == 0)
        {
          this->pAutomaticTask->setActive(false);
          this->pManualTask->setActive(true);
        }

        if (this->pAutomaticTask->isActive())
        {
          this->pAutomaticTask->changeState(this->pAutomaticTask->getStateFromString(state));
        }
        else if (this->pManualTask->isActive())
        {
          this->pManualTask->changeState(this->pManualTask->getStateFromString(state));
        }

        this->pUserPanel->saveTemperature((float)atof(temperature.c_str()));
        MsgService.sendMsg("WINDOW:" + String(this->pUserPanel->getWindowOpeningPercentage()));
      }
    }
    delete msg;
  }
  if (this->pUserPanel->isButtonModePressed())
  {
    this->notifyChangeMode();
  }
}
