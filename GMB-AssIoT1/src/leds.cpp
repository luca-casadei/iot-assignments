#include <Arduino.h>
#include "leds.h"
#include "pins.h"

#define FADE_START 0
#define STEP_MULTIPLIER 15

static unsigned char leds[LED_N] = {LED_1, LED_2, LED_3, LED_4};
static unsigned char states[LED_N];
static unsigned short fade_amount;
static short step;

void shut_leds(void) {
  int i;
  for (i = 0; i < LED_N; i++) {
    digitalWrite(leds[i], LOW);
  }
  states[0] = states[1] = states[2] = states[3] = LOW;
}

void set_led_state(unsigned int led_index){
  states[led_index] = ((states[led_index]) == LOW ? HIGH : LOW);
  digitalWrite(leds[led_index], states[led_index]);
}

void set_analog_red_led(int amount){
  analogWrite(LED_WRONG, amount);
}

void initialize_leds(void){
  fade_amount = FADE_START;
  step = STEP_MULTIPLIER;
  int i;
  for(i = 0; i < LED_N; i++){
    pinMode(leds[i], OUTPUT);
  }
  pinMode(LED_WRONG, OUTPUT);
  states[0] = states[1] = states[2] = states[3] = LOW;
}

void fade()
{
  analogWrite(LED_WRONG, fade_amount);
  fade_amount += step;
  if (fade_amount <= 0 || fade_amount >= 255)
  {
    step = -step;
  }
}