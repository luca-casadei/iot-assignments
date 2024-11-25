#include "constants.hpp"
#include "tasks/Scheduler.hpp"
#include "tasks/SleepingTask.hpp"
#include <Arduino.h>
#include "components/Led.hpp"
#include "components/LCD.hpp"

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
    Serial.begin(BAUD);
    // Components
    pinMode(MOTION_DETECTOR, INPUT);
    LCD *lcd = new LCD(LCD_ADDR, LCD_COLS, LCD_ROWS);
    lcd->init();
    // Tasks
    // Sleeping task
    Task *sleep = new SleepingTask(MOTION_DETECTOR, 5, lcd);
    sleep->init(TASK_SLEEP_PERIOD);

    // Scheduler
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