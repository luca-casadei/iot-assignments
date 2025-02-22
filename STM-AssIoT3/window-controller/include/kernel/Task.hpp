#pragma once

class Task
{

public:
  Task()
  {
    active = false;
  }

  /* periodic */
  virtual void init(const int period)
  {
    myPeriod = period;
    periodic = true;
    active = true;
    timeElapsed = 0;
  }

  /* aperiodic */
  virtual void init()
  {
    timeElapsed = 0;
    periodic = false;
    active = true;
    completed = false;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(const int basePeriod)
  {
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod)
    {
      timeElapsed = 0;
      return true;
    }
    else
    {
      return false;
    }
  }

  void setCompleted()
  {
    completed = true;
    active = false;
  }

  bool isCompleted()
  {
    return completed;
  }

  bool isPeriodic()
  {
    return periodic;
  }

  bool isActive()
  {
    return active;
  }

  virtual void setActive(const bool active)
  {
    timeElapsed = 0;
    this->active = active;
  }

private:
  int myPeriod;
  int timeElapsed;
  bool active;
  bool periodic;
  bool completed;
};
