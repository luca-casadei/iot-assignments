#include <Arduino.h>
#include <EnableInterrupt.h>
#include "buttons.h"
#include "game.h"

// unsigned int btns[BTN_N] = { BTN_1, BTN_2, BTN_3, BTN_4 };
uint8_t button_states[BTN_N] = {LOW, LOW, LOW, LOW};

void set_state_button(unsigned int button_index, uint8_t state){
    button_states[button_index] = state;
    increase_curr_bin_amount(button_index, state == HIGH);
}

static void button_pressed(unsigned int btn_pin){
    if (button_states[btn_pin] == HIGH){
        set_state_button(btn_pin, LOW);
    } else {
        set_state_button(btn_pin, HIGH);
    }
    delay(BOUNCING_PREVENTION_TIME);
}

static void button_pressed_1(void){
    button_pressed(0);
}

static void button_pressed_2(void){
    button_pressed(1);
}

static void button_pressed_3(void){
    button_pressed(2);
}

static void button_pressed_4(void){
    button_pressed(3);
}

static void button_pressed_1_start_game(){
    game_start();
    enableInterrupt(BTN_1, button_pressed_1, RISING);
    enableInterrupt(BTN_2, button_pressed_2, RISING);
    enableInterrupt(BTN_3, button_pressed_3, RISING);
    enableInterrupt(BTN_4, button_pressed_4, RISING);
    delay(BOUNCING_PREVENTION_TIME);
}

void initialize_buttons(void){
   pinMode(BTN_1, INPUT);
   pinMode(BTN_2, INPUT);
   pinMode(BTN_3, INPUT);
   pinMode(BTN_4, INPUT);
   enableInterrupt(BTN_1, button_pressed_1_start_game, RISING);
}

