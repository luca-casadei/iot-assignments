#include <Arduino.h>
#include "game.h"
#include "leds.h"
#include "buttons.h"
#include "potentiometer.h"

#define START_TIME_SEC 10
#define MICRO_MUL 1000000
#define GAMEOVER_DELAY_MS 1000

/* The currently selected amount by lighting the LEDs */
unsigned short current_bin_value;
/* Random correct value to select by lighting the LEDs */
unsigned short correct_bin_value;
/* The player's score */
unsigned int score;
/* The current state of the game */
enum game_state current_state;
/* Time in microseconds for the game to end */
unsigned int time_us;

unsigned short get_current_binary_value(void)
{
    return current_bin_value;
}

void increase_curr_bin_amount(unsigned int amount_index, bool increase)
{
    static unsigned short bins[4] = {8, 4, 2, 1};
    current_bin_value = current_bin_value + increase ? bins[amount_index] : -bins[amount_index];
    set_led_state(amount_index, increase ? HIGH : LOW);
}

void increment_score(void)
{
    score++;
}

unsigned int get_score(void)
{
    return score;
}

unsigned short int random_bin_value(void)
{
    return rand() % 15;
}

void initialize_game(void)
{
    randomSeed(micros());
    correct_bin_value = random_bin_value();
    score = 0;
    current_bin_value = 0;
    time_us = START_TIME_SEC;
    current_state = BLINKING;
}

bool round_won(void)
{
    return current_bin_value == correct_bin_value;
}

void game_start(void)
{
    current_state = RUNNING;
    set_analog_red_led(LOW);
    // TODO
}

void game_sleep(void)
{
    current_state = SLEEPING;
    // TODO
}

void game_blink(void)
{
    current_state = BLINKING;
    // TODO
}

void next_turn(void)
{
    correct_bin_value = random_bin_value();

    shut_leds();
}

void timesUpHandler()
{
    if (round_won())
    {
        next_turn();
    }
    else
    {
        set_analog_red_led(255);
        shut_leds();
        delay(GAMEOVER_DELAY_MS);
        time_us = START_TIME_SEC;
        current_state = BLINKING;
    }
}

enum game_state get_game_state(void)
{
    return current_state;
}