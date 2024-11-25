#pragma once
#include "TaskWithCounter.hpp"

class LCD;

class SleepingTask : public TaskWithCounter
{

private:
  unsigned int motionDetectorPin;
  unsigned int counter;
  LCD * lcd;
  enum {
    AWAKE,
    SLEEPING
  } state;

public:
  SleepingTask(unsigned int motionDetectorPin, unsigned int seconds_before_sleeping, LCD * lcd);
  void init(unsigned int period) final;
  void tick() final;
};
