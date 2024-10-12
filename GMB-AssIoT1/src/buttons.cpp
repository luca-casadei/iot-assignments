#include <Arduino.h>
#include "interrupts.h"
#include "buttons.h"
#include "game.h"

#define DEBUG

unsigned char button_states[BTN_N];

void set_state_button(unsigned int button_index, unsigned char state)
{
    button_states[button_index] = state;
    increase_curr_bin_amount(button_index, state == HIGH);
}

static void button_pressed(unsigned int btn_pin)
{
    set_state_button(btn_pin, button_states[btn_pin] == HIGH ? LOW : HIGH);
    delay(BOUNCING_PREVENTION_TIME);
}

static void button_pressed_1(void)
{
    button_pressed(0);
}

static void button_pressed_2(void)
{
    button_pressed(1);
}

static void button_pressed_3(void)
{
    button_pressed(2);
}

static void button_pressed_4(void)
{
    button_pressed(3);
}

void disable_every_button(void){
    disable_interrupt_to(BTN_1);
    disable_interrupt_to(BTN_2);
    disable_interrupt_to(BTN_3);
    disable_interrupt_to(BTN_4);
}

static void button_pressed_1_start_game()
{
    game_start();
    enable_interrupt_to(BTN_1, button_pressed_1);
    enable_interrupt_to(BTN_2, button_pressed_2);
    enable_interrupt_to(BTN_3, button_pressed_3);
    enable_interrupt_to(BTN_4, button_pressed_4);
    delay(BOUNCING_PREVENTION_TIME);
}

void initialize_buttons(void)
{
    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);
    pinMode(BTN_4, INPUT);
    disable_interrupt_to(BTN_2);
    disable_interrupt_to(BTN_3);
    disable_interrupt_to(BTN_4);
    button_states[0] = button_states[1] = button_states[2] = button_states[3] = LOW;
    enable_interrupt_to(BTN_1, button_pressed_1_start_game);
}
