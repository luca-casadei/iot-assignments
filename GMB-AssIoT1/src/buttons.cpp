#include <Arduino.h>
#include "buttons.h"
#include "game.h"

unsigned int btns[BTN_N] = { BTN_1, BTN_2, BTN_3, BTN_4 };
uint8_t button_states[BTN_N] = {LOW, LOW, LOW, LOW};

void initialize_buttons(){
   int i;
   for(i = 0; i < BTN_N; i++){
    pinMode(btns[i], INPUT);
   }
}

void set_state_button(unsigned int button_index, uint8_t state){
    button_states[button_index] = state;
    unsigned short bin_val = get_bin_vals()[button_index];
    increase_curr_bin_amount(state == HIGH ? bin_val : -bin_val);
}

bool is_button_state_high(uint8_t button_pin){
    return digitalRead(button_pin) == HIGH ? true : false;
}

uint8_t get_pressed_state(unsigned int btn_index){
    return button_states[btn_index];
}