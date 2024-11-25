#include <avr/power.h>
#include <avr/sleep.h>
#include "components/LCD.hpp"
#include "tasks/SleepingTask.hpp"
#include <Arduino.h>
#include "EnableInterrupt.h"

SleepingTask::SleepingTask(unsigned int motionDetectorPin, unsigned int seconds_before_sleeping, LCD *lcd) : TaskWithCounter(seconds_before_sleeping)
{
  this->motionDetectorPin = motionDetectorPin;
  this->lcd = lcd;
}

void wake_up(){

}

void SleepingTask::init(unsigned int period)
{
  TaskWithCounter::init(period);
  state = AWAKE;
  this->counter = 0;
  enableInterrupt(this->motionDetectorPin, wake_up, CHANGE);
}

void SleepingTask::tick()
{
  const int PIR = digitalRead(this->motionDetectorPin);
  switch (this->state)
  {
  case AWAKE:
  {
    if (PIR == HIGH)
    {
      this->counter = 0;
    }
    else
    {
      if (this->counter < this->get_counter_max())
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
