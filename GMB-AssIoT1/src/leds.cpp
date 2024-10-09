#include <Arduino.h>
#include "leds.h"

uint8_t leds[LED_N] = {LED_1, LED_2, LED_3, LED_4};

void shut_leds(void) {
  int i;
  for (i = 0; i < LED_N; i++) {
    set_led_state(leds[i], LOW);
  }
}

void set_led_state(unsigned int led_index, uint8_t state){
  digitalWrite(leds[led_index], state);
}

void set_analog_red_led(int amount){
  analogWrite(LED_WRONG, amount);
}

void initialize_leds(void){
  int i;
  for(i = 0; i < LED_N; i++){
    pinMode(leds[i], OUTPUT);
  }
  pinMode(LED_WRONG, OUTPUT);
}