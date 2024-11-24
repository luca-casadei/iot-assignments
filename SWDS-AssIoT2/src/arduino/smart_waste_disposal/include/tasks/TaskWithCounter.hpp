#include "Task.hpp"

class TaskWithCounter : public Task
{
protected:
    /**
     * Gets the amount of times that the counter must iterate before reaching the time deadline.
     */
    unsigned int counter_calc(unsigned int seconds, unsigned int task_period)
    {
        return (seconds * 1000U) / task_period;
    }
};