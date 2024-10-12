#include <Arduino.h>
#include <TimerOne.h>
#include <avr/sleep.h>
#include "timers.h"
#include "interrupts.h"
#include "game.h"
#include "potentiometer.h"
#include "buttons.h"

#define DEBUG

/* Time in microseconds for the game to end */
unsigned long time_us = START_TIME_SEC;
static bool tinit = false;

void wake_up(void)
{
    game_blink();
}

void go_to_sleep(void)
{
#ifdef DEBUG
    Serial.println("Entering a deep sleep...");
#endif
    interrupts();
    game_sleep();
    enable_interrupt_to(BTN_1, wake_up);
    enable_interrupt_to(BTN_2, wake_up);
    enable_interrupt_to(BTN_3, wake_up);
    enable_interrupt_to(BTN_4, wake_up);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    noInterrupts();
}

void initialize_sleep_timer(void)
{
    detach_timer();
    if (!tinit){
        Timer1.initialize(MICRO_MUL * GOTO_SLEEP_TIME);
    }
    else{
        Timer1.setPeriod(MICRO_MUL * GOTO_SLEEP_TIME);
    }
    tinit = true;
    Timer1.attachInterrupt(go_to_sleep);
#ifdef DEBUG
    Serial.print("Intializing sleep timer with time of s: ");
    Serial.print(GOTO_SLEEP_TIME);
    Serial.println();
#endif
}

void initialize_game_over_timer(void)
{
    time_us = time_us - choose_difficulty() * F_FACTOR;
    if (time_us <= MIN_TIME_VAL)
    {
        time_us = MIN_TIME_VAL;
    }
    detach_timer();
    Timer1.setPeriod(MICRO_MUL * time_us);
    Timer1.attachInterrupt(game_over);
#ifdef DEBUG
    Serial.print("Intializing game timer with time of s: ");
    Serial.print(time_us);
    Serial.println();
#endif
}

void detach_timer(void)
{
    Timer1.detachInterrupt();
}