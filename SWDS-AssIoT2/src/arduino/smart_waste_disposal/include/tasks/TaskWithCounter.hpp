#include "Task.hpp"

class TaskWithCounter : public Task
{
protected:
    virtual void init(unsigned int period);
    unsigned int get_counter_max();
    TaskWithCounter(unsigned int seconds);

private:
    unsigned int counter_max;
    unsigned int seconds;
    unsigned int counter_calc(unsigned int seconds, unsigned int task_period);
};