#pragma once

class Task
{
private:
  unsigned int myPeriod;
  unsigned int timeElapsed;

protected:
  unsigned int get_period()
  {
    return this->myPeriod;
  }

public:
  virtual void init(unsigned int period)
  {
    myPeriod = period;
    timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(unsigned int basePeriod)
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
};
