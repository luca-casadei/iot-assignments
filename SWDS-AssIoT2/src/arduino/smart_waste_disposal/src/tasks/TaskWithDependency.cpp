#include "tasks/TaskWithDependency.hpp"

void TaskWithDependency::add_dependency(Task * dep){
    this->dependencies[this->curr_index] = dep;
    this->curr_index++;
}