#include <Arduino.h>
#include <TimerOne.h>
#include "timers.h"
#include "interrupts.h"
#include "pins.h"
#include "potentiometer.h"

#define DEBUG

/* Time in microseconds for the game to end */
unsigned long time_us = START_TIME_SEC;

void initialize_timerone(void)
{
    time_us = START_TIME_SEC;
    Timer1.initialize(MICRO_MUL * GOTO_SLEEP_TIME);
}

void set_sleep_timer(void)
{
    Timer1.setPeriod(MICRO_MUL * GOTO_SLEEP_TIME);
    Timer1.attachInterrupt(sleep_timer_elapsed);
}

void set_game_timer(void)
{
    Timer1.setPeriod(MICRO_MUL * time_us);
    Timer1.attachInterrupt(game_timer_elapsed);
    time_us = time_us - (F_FACTOR * choose_difficulty());
    if (time_us < MIN_TIME_VAL){
        time_us = MIN_TIME_VAL;
    }
}

void detach_timerone(void)
{
    Timer1.detachInterrupt();
}