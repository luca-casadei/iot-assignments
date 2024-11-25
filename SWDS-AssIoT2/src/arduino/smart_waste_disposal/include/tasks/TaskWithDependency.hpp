#pragma once

#include "Task.hpp"

class TaskWithDependency : public Task{
    TaskWithDependency() : Task() {};
    virtual void init() = 0;
    protected:
    void add_dependency(Task * dep);
    private:
    Task ** dependencies;
    unsigned int curr_index;
};