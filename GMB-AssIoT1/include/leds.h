/* Four green LEDs */
#define LED_1 8
#define LED_2 9
#define LED_3 10
#define LED_4 11

#define LED_N 4

/* Fading and game over red LED */
#define LED_WRONG 6

/*
  Shuts down every LED in the collection.
*/
void shut_leds(void);

/*
  Sets the analog value of the red LED.
*/
void set_analog_red_led(int amount);

/*
  Sets the LED state to LOW or HIGH.
*/
void set_led_state(unsigned int led_index, uint8_t state);

/*
    Sets every LED pin to OUTPUT
*/
void initialize_leds(void);