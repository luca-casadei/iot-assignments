#include "tasks/Scheduler.hpp"
#include "tasks/SleepingTask.hpp"
#include "tasks/WasteTask.hpp"
#include "tasks/TemperatureTask.hpp"
#include "components/Led.hpp"
#include "components/LCD.hpp"
#include <Arduino.h>
#include "constants.hpp"

// #define TEST_COMPONENTS

#ifdef TEST_COMPONENTS
#include "components/ComponentTester.hpp"
ComponentTester *tester;
#else
Scheduler scheduler;
#endif

void setup()
{
#ifdef TEST_COMPONENTS
    tester = new ComponentTester(GREEN_PIN, RED_PIN, SERVO_PIN);
    tester->init();
#else
    Serial.begin(BAUD);

    // Components
    LCD *lcd = new LCD(LCD_ADDR, LCD_COLS, LCD_ROWS);
    lcd->init();

    // Tasks
    // Sleeping task
    Task *sleep = new SleepingTask(MOTION_DETECTOR, lcd, 5);
    sleep->init(TASK_SLEEP_PERIOD);
    // Temperature Task
    TemperatureTask *temp = new TemperatureTask(TEMPERATURE_SENSOR, TEMPERATURE_THRESHOLD, MAX_TEMP_TIME);
    temp->init(TASK_TEMP_PERIOD);

    Task *waste = new WasteTask(GREEN_PIN,
                                RED_PIN, OPEN_PIN,
                                CLOSE_PIN,
                                ECHO,
                                TRIG, MAX_ENT_TIME,
                                MAX_RECV_TIME, MAX_EMPTY_TIME,
                                TRASHTRESH_CM, SERVO_PIN, temp, lcd);
    waste->init(100);

    // Scheduler
    scheduler.init(SCHEDULER_MCD_PERIOD);
    scheduler.addTask(sleep);
    scheduler.addTask(temp);
    scheduler.addTask(waste);
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