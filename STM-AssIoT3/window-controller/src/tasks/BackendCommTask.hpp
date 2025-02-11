#ifndef __OPERATOR_MAN_TASK__
#define __OPERATOR_MAN_TASK__

#include "kernel/Task.hpp"
#include "model/Dashboard.hpp"

enum State{ NORMAL, HOT, TOO_HOT, ALARM };

class BackendCommTask: public Task {

public:
  BackendCommTask(Dashboard* pDashboard); 
  void tick();

private:  
  void setState(State state);
  long elapsedTimeInState();
  void log(const String& msg);
  State state;
  
  bool checkAndSetJustEntered();
  
  long stateTimestamp;
  bool justEntered;

  Dashboard* pDashboard;

};

#endif