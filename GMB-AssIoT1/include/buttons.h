#include <Arduino.h>

#define BTN_1 12
#define BTN_2 3
#define BTN_3 4
#define BTN_4 5

#define BTN_N 4

/*
    Sets every button to INPUT.
*/
void intialize_buttons(void);

/*
    Gets the HIGH or LOW state of the button.
    true if HIGH, false if LOW.
*/
bool is_button_state_high(uint8_t button_pin);

/*
Gets the current state of pressed buttons. 
*/
uint8_t get_pressed_state(unsigned int button_index);