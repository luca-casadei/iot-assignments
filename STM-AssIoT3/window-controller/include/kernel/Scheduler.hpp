#pragma once

#include "Task.hpp"

#define MAX_TASKS 50

class Scheduler
{

  int basePeriod;
  int nTasks;
  Task *taskList[MAX_TASKS];

public:
  void init(const int basePeriod);
  virtual bool addTask(Task *task);
  virtual void schedule();
};
