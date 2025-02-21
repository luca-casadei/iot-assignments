#pragma once

#include "kernel/TaskWithState.hpp"

class AutomaticTask : public TaskWithState
{

public:
  AutomaticTask();
  void tick();
  void changeState(State newState);

private:
  long elapsedTimeInState();
  bool checkAndSetJustEntered();
  
};