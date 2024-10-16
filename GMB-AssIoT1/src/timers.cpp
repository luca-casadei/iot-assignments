#include <Arduino.h>
#include "timers.h"
#include "interrupts.h"
#include "pins.h"
#include "potentiometer.h"

#define DEBUG

/* Time in microseconds for the game to end */
volatile unsigned long time;
volatile unsigned long last_time;

void set_game_timer(void)
{
    time = START_TIME_SEC;
    last_time = millis();
}

void set_sleep_timer(void){
    time = GO_TO_SLEEP_TIME;
    last_time = millis();
}

void check_sleep_timer(void)
{
    unsigned long curr_time = millis();
    if ((curr_time - last_time) >= time * MILLIS_MUL){
        sleep_timer_elapsed();
        last_time = curr_time;
    }
}

void check_game_timer(void)
{
    unsigned long curr_time = millis();
    if((curr_time - last_time) >= MILLIS_MUL * time){
        game_timer_elapsed();
        last_time = curr_time;
    }
}

void delay_millis(unsigned long time_ms){
    unsigned long curr_time = millis();
    unsigned long t = curr_time;
    while(t <= (curr_time + time_ms)){
        t = millis();
    }
}