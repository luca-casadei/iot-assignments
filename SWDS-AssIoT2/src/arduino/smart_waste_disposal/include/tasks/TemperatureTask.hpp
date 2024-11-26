#pragma once
#include "TaskWithCounter.hpp"

class TemperatureSensor;

class TemperatureTask : public TaskWithCounter
{

private:
  unsigned int counter;
  unsigned int max_temp;
  unsigned int max_temp_time;
  TemperatureSensor * temperature_sensor;
  enum {
    STABLE,
    UNSTABLE,
    DANGER
  } state;

public:
  TemperatureTask(unsigned int temp_pin, unsigned int max_temp, unsigned int max_temp_time);
  void init(unsigned int period) final;
  void tick() final;
  bool isInDanger();
  double getTemp();
};
