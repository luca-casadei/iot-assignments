#include <Arduino.h>
#include "game.h"

static GameState state;
static unsigned int score;
static unsigned short solution_value;
static unsigned short chosen_value;
static const unsigned short BINS[4] = {8, 4, 2, 1};
static bool STATES[4];

GameState get_game_state()
{
    return state;
}

void initialize_game(void)
{
    state = BLINKING;
    randomSeed(micros());
}

bool game_won(void)
{
    return solution_value == chosen_value;
}

/* State setters */
void game_blink(void)
{
    state = BLINKING;
}

void game_sleep(void)
{
    state = SLEEPING;
}

void toggle_binary(unsigned short index)
{
    chosen_value = chosen_value + (STATES[index] ? -BINS[index] : BINS[index]);
    STATES[index] = !STATES[index];
}

void game_run(void)
{
    score = 0;
    chosen_value = 0;
    solution_value = rand() % 16;
    state = RUNNING;
    STATES[0] = STATES[1] = STATES[2] = STATES[3] = false;
}

void next_round(void)
{
    score++;
    chosen_value = 0;
    solution_value = rand() % 16;
    STATES[0] = STATES[1] = STATES[2] = STATES[3] = false;
}

unsigned short get_score()
{
    return score;
}
unsigned short get_correct_value()
{
    return solution_value;
}