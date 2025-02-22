#pragma once

#include "model/UserPanel.hpp"
#include "Task.hpp"

class TaskWithUserPanel : public Task
{
public:
    void setUserPanel(UserPanel* pUserPanel);
    UserPanel* getUserPanel();

protected:
    UserPanel* pUserPanel;
};
