#pragma once
#include "TaskWithCounter.hpp"

class LCD;
class MotionDetector;

class SleepingTask : public TaskWithCounter
{

private:
  unsigned int counter;
  LCD * lcd;
  MotionDetector * pir;
  enum {
    AWAKE,
    SLEEPING
  } state;

public:
  SleepingTask(unsigned int motion_detector_pin, LCD * lcd, unsigned int time_before_sleep);
  void init(unsigned int period) final;
  void tick() final;
};
