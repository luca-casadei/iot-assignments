#include <avr/power.h>
#include <avr/sleep.h>
#include "components/LCD.hpp"
#include "components/MotionDetector.hpp"
#include "tasks/SleepingTask.hpp"
#include "EnableInterrupt.h"

SleepingTask::SleepingTask(unsigned int motion_detector_pin, LCD * lcd, unsigned int time_before_sleep): TaskWithCounter(1)
{
  this->pir = new MotionDetector(motion_detector_pin);
  this->lcd = lcd;
  this->add_time(time_before_sleep);
}

void wake_up()
{
}

void SleepingTask::init(unsigned int period)
{
  Task::init(period);
  this->state = AWAKE;
  this->counter = 0;
  enableInterrupt(this->pir->getPin(), wake_up, RISING);
}

void SleepingTask::tick()
{
  const bool detected = this->pir->detected();
  switch (this->state)
  {
  case AWAKE:
  {
    if (detected)
    {
      this->counter = 0;
    }
    else
    {
      if (this->counter < this->get_iterations())
      {
        this->counter++;
      }
      else
      {
        this->state = SLEEPING;
      }
    }

    break;
  }
  case SLEEPING:
  {
    lcd->off();
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
    lcd->on();
    break;
  }
  }
}
