#include "constants.hpp"
#include "tasks/Scheduler.hpp"
#include "tasks/SleepingTask.hpp"
#include <Arduino.h>
#include "components/Led.hpp"

// #define TEST_COMPONENTS

#ifdef TEST_COMPONENTS
#include "components/ComponentTester.hpp"
IComponentTester *tester;
#else
Scheduler scheduler;
#endif

void setup()
{
#ifdef TEST_COMPONENTS
    tester = new ComponentTester(GREEN_PIN, RED_PIN, SERVO_PIN);
    tester->init();
    MsgService.init();
#else
//Tasks
//Sleeping task
Task * sleep = new SleepingTask(MOTION_DETECTOR, 5);
sleep->init(TASK_SLEEP_PERIOD);

//Scheduler
scheduler.init(SCHEDULER_MCD_PERIOD);
scheduler.addTask(sleep);
#endif
}

void loop()
{
#ifdef TEST_COMPONENTS
    tester->test();
#else
    scheduler.schedule();
#endif
}