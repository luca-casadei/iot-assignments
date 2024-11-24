#pragma once
#include "TaskWithCounter.hpp"

class SleepingTask : public TaskWithCounter
{

private:
  unsigned int motionDetectorPin;
  unsigned int counter;
  unsigned int time_before_sleeping;
  unsigned int seconds_before_sleeping;
  enum {
    AWAKE,
    SLEEPING
  } state;

public:
  SleepingTask(unsigned int motionDetectorPin, unsigned int seconds_before_sleeping);
  virtual void init(unsigned int period) final;
  virtual void tick() final;
};
