#include <Arduino.h>

#define BTN_1 2
#define BTN_2 3
#define BTN_3 4
#define BTN_4 5

#define BTN_N 4

/*
  Time in ms to prevent bouncing 
*/
#define BOUNCING_PREVENTION_TIME 20

/*
  Sets every button to INPUT.
*/
void initialize_buttons(void);


/*
  Gets the current state of pressed buttons. 
*/
uint8_t get_pressed_state(unsigned int button_index);

/*
  Sets the state of the button.
  LOW - Not pressed
  HIGH - Pressed
*/
void set_state_button(unsigned int button_index, uint8_t state);