#include "tasks/TaskWithCounter.hpp"
#include <stdlib.h>

TaskWithCounter::TaskWithCounter(unsigned int max_times_amount) : Task() {
    this->times = (unsigned int *)malloc(sizeof(unsigned int) * max_times_amount);
    this->curr_index = 0;
}

TaskWithCounter::~TaskWithCounter(){
    free(this->times);
}

void TaskWithCounter::add_time(unsigned int time){
    this->times[curr_index] = time;
    this->curr_index++;
}

unsigned int TaskWithCounter::counter_calc(unsigned int seconds, unsigned int period)
{
    return (seconds * 1000U) / period;
}

unsigned int TaskWithCounter::get_iterations(unsigned int index){
    return index < this->max_times_amount ? counter_calc(this->times[index], this->get_period()) : 0;
}

unsigned int TaskWithCounter::get_iterations(void){
    return counter_calc(get_iterations(0), this->get_period());
}