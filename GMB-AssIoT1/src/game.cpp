#include <Arduino.h>
#include "game.h"

/* The currently selected amount by lighting the LEDs */
unsigned short current_bin_value;
/* Random correct value to select by lighting the LEDs */
unsigned short correct_bin_value;
/* The player's score */
unsigned int score;

unsigned short get_current_binary_value(void){
    return current_bin_value;
}

unsigned short * get_bin_vals(){
    static unsigned short bins[4] = {8, 4, 2, 1};
    return bins;
}

void increase_curr_bin_amount(short amount){
    current_bin_value += amount;
}

void increment_score(void){
    score++;
}

unsigned int get_score(void){
    return score;
}

void initialize_game(void){
    srand(micros());
    correct_bin_value = rand() % 15;
    score = 0;
    #ifdef DEBUG
    Serial.print("Valore corretto casuale: ");
    Serial.print(correct_bin_value);
    Serial.println();
    #endif
}

bool round_won(void){
    return current_bin_value == correct_bin_value;
}