#include <Arduino.h>
#include "game.h"
#include "leds.h"
#include "buttons.h"
#include "potentiometer.h"
#include "timers.h"

#define DEBUG

/* The currently selected amount by lighting the LEDs */
unsigned short current_bin_value;
/* Random correct value to select by lighting the LEDs */
unsigned short correct_bin_value;
/* The player's score */
unsigned int score;
/* The current state of the game */
enum game_state current_state;

enum round_state round_state;

unsigned short get_current_binary_value(void)
{
    return current_bin_value;
}

void increase_curr_bin_amount(unsigned int amount_index, bool increase)
{
    static unsigned short bins[4] = {8, 4, 2, 1};
    current_bin_value = current_bin_value + (increase ? bins[amount_index] : -(bins[amount_index]));
    set_led_state(amount_index, increase ? HIGH : LOW);
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
    initialize_buttons();
    initialize_potentiometer();
    initialize_leds();
    randomSeed(micros());
    current_state = BLINKING;
    initialize_sleep_timer();
}

void game_start(void)
{
    round_state = WAITING;
    current_state = RUNNING;
    score = 0;
    current_bin_value = 0;
    correct_bin_value = random_bin_value();
    shut_leds();
    set_analog_red_led(LOW);
    initialize_game_over_timer();
}

void game_sleep(void)
{
    current_state = SLEEPING;
}

void game_blink(void)
{
    current_state = BLINKING;
    initialize_buttons();
    initialize_sleep_timer();
}

void game_over(void)
{
#ifdef DEBUG
    Serial.print("Correct value: ");
    Serial.print(correct_bin_value);
    Serial.println();
    Serial.print("Current value: ");
    Serial.print(current_bin_value);
    Serial.println();
#endif
    round_state = current_bin_value == correct_bin_value ? WON : LOST;
    if(round_state == LOST){
        disable_every_button();
    }
#ifdef DEBUG
    Serial.print(round_state == WON ? "Next turn for you..." : "You lost... Returning to blinking");
    Serial.println();
#endif
}

void next_turn(void)
{
    score++;
    correct_bin_value = random_bin_value();
    current_bin_value = 0;
    round_state = WAITING;
    initialize_game_over_timer();
}

enum game_state get_game_state(void)
{
    return current_state;
}

enum round_state round_won(void)
{
    return round_state;
}