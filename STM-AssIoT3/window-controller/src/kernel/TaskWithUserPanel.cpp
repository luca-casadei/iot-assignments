#include "kernel/TaskWithUserPanel.hpp"

void TaskWithUserPanel::setUserPanel(UserPanel *pUserPanel)
{
    this->pUserPanel = pUserPanel;
}

UserPanel *TaskWithUserPanel::getUserPanel()
{
    return this->pUserPanel;
}