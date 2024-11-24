#include <avr/power.h>
#include <avr/sleep.h>
#include "tasks/SleepingTask.hpp"

SleepingTask::SleepingTask(unsigned int motionDetectorPin, unsigned int seconds_before_sleeping)
{
  this->motionDetectorPin = motionDetectorPin;
  this->seconds_before_sleeping = seconds_before_sleeping;
}

void SleepingTask::init(unsigned int period)
{
  Task::init(period);
  state = AWAKE;
  this->counter = 0;
  this->time_before_sleeping = this->counter_calc(this->seconds_before_sleeping, period);
}

void SleepingTask::tick()
{
  switch (this->state)
  {
  case AWAKE:
  {
    if (this->counter < this->time_before_sleeping)
    {
      this->counter++;
    }
    else
    {
      this->state = SLEEPING;
    }
    break;
  }
  case SLEEPING:
  {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    power_adc_disable();
    power_twi_disable();
    power_spi_disable();
    power_timer0_disable();
    power_timer2_disable();
    sleep_mode();
    sleep_disable();
    power_all_enable();
    this->state = AWAKE;
    this->counter = 0;
    break;
  }
  }
}
