#include <Arduino.h>
#include "timers.h"
#include "interrupts.h"
#include "pins.h"

// #define DEBUG

#define START_TIME_SEC 20L
#define SLEEP_TIME_SEC 10L
#define MIN_GAME_TIME_SEC 5L
#define MILLIS_MUL 1000UL
#define F_FACTOR 2L

/* Time in microseconds for the game to end */
static volatile long game_time = -1;
static volatile unsigned long sleep_time;
static volatile unsigned long last_time;
static volatile unsigned long last_fade_time;

void reset_game_timer(void){
    game_time = -1;
}

void set_game_timer(long difficulty)
{
    if (game_time == -1)
    {
        game_time = START_TIME_SEC;
    }
    else
    {
#ifdef DEBUG
        Serial.print("Old time: ");
        Serial.println(game_time);
#endif
        game_time = game_time - (F_FACTOR * difficulty);
        if (game_time < MIN_GAME_TIME_SEC)
        {
            game_time = MIN_GAME_TIME_SEC;
        }
#ifdef DEBUG
        Serial.print("Current time: ");
        Serial.println(game_time);
#endif
    }
    last_time = millis();
}

void set_sleep_timer(void)
{

    sleep_time = SLEEP_TIME_SEC;
    last_time = millis();
}

static void check_timer(void (*f)(void), long time)
{
    const unsigned long curr_time = millis();
    if ((curr_time - last_time) >= time * MILLIS_MUL)
    {
        f();
        last_time = curr_time;
    }
}

void check_sleep_timer(void)
{
    check_timer(sleep_timer_elapsed, sleep_time);
}

void check_game_timer(void)
{
    check_timer(game_timer_elapsed, game_time);
}

bool check_fade_timer(void)
{
    const unsigned long curr_time = millis();
    if ((curr_time - last_fade_time) >= 50UL)
    {
        last_fade_time = curr_time;
        return true;
    }
    else
    {
        return false;
    }
}

void delay_millis(unsigned long time_ms)
{
    const unsigned long curr_time = millis();
    unsigned long t = curr_time;
    while (t <= (curr_time + time_ms))
    {
        t = millis();
    }
}