#pragma once

#include "kernel/TaskWithState.hpp"
#include "kernel/TaskWithUserPanel.hpp"

class AutomaticTask : public TaskWithState, public TaskWithUserPanel
{

public:
  AutomaticTask(UserPanel *pUserPanel);
  void tick();
  void changeState(State newState);

};