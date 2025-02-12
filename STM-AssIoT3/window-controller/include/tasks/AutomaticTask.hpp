#pragma once

#include "kernel/Task.hpp"
#include "model/Dashboard.hpp"

class AutomaticTask : public Task
{

public:
  AutomaticTask(Dashboard *pDashboard);
  void tick();

private:
  enum State
  {
    NORMAL,
    HOT,
    TOO_HOT,
    ALARM
  };
  void setState(State state);
  long elapsedTimeInState();
  void log(const String &msg);
  State state;

  bool checkAndSetJustEntered();

  long stateTimestamp;
  bool justEntered;

  Dashboard *pDashboard;
};