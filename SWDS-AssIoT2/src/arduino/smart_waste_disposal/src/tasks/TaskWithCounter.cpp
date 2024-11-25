#include "tasks/TaskWithCounter.hpp"

TaskWithCounter::TaskWithCounter(unsigned int seconds): Task()
{
    this->seconds = seconds;
}

void TaskWithCounter::init(unsigned int period)
{
    Task::init(period);
    this->counter_max = this->counter_calc(seconds, period);
}

unsigned int TaskWithCounter::get_counter_max(){
    return this->counter_max;
}

unsigned int TaskWithCounter::counter_calc(unsigned int seconds, unsigned int period)
{
    return (seconds * 1000U) / period;
}