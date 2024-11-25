#pragma once

#include "Task.hpp"

class TaskWithCounter : public Task
{
protected:
    TaskWithCounter(unsigned int max_times_amount);
    virtual ~TaskWithCounter();
    unsigned int get_iterations(unsigned int index);
    unsigned int get_iterations(void);
    void add_time(unsigned int time);

private:
    unsigned int * times;
    unsigned int counter_calc(unsigned int seconds, unsigned int task_period);
    
    unsigned int max_times_amount;
    unsigned int curr_index;
};