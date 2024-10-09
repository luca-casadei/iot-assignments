#define DEBUG

/*
	Luca Casadei
  Francesco Pazzaglia
  Lucio Baiocchi
*/

#include <Arduino.h>
#include <TimerOne.h>
#include "leds.h"
#include "buttons.h"
#include "game.h"

#define START_TIME_SEC 10

#define MICRO_MUL 1000000

#define LOOP_DELAY_MS 100
#define GAMEOVER_DELAY_MS 1000

/* Game values */
unsigned int time_us;
unsigned short correct_answer;
unsigned int game_started;

void nextTurn() {
  initialize_game();
  /* Sets the value to be converted in binary */
  shut_leds();
  
  /* TODO: Decrease time on next turn */
  unsigned int pot_f = analogRead(A5) / 255;
  unsigned int f_factor = ((pot_f * 5) / 3);
  time_us = (time_us - f_factor);

  #ifdef DEBUG
    Serial.print("Tempo: ");
    Serial.print(time_us);
    Serial.println();
  #endif

  /* Sets the timer for game over */
  // Timer1.initialize(time_us * MICRO_MUL);
  // Timer1.attachInterrupt(timesUpHandler);
}

void timesUpHandler() {
  if (round_won()) {
    nextTurn();
  } else {
    set_analog_red_led(255);
    shut_leds();
    delay(GAMEOVER_DELAY_MS);
    game_started = 0;
    time_us = START_TIME_SEC;
    Timer1.detachInterrupt();
  }
}

unsigned short fade_amount;
short step;

void setup() {
  Serial.begin(9600);

  /* See function for behaviour */
  time_us = START_TIME_SEC;

  /* Activates Arduino's pins */
  initialize_leds();
  initialize_game();

  // TODO: Potentiometer
  pinMode(A5, INPUT);

  fade_amount = 0;
  game_started = 0;
  step = 51;
}

/* Checks if the analog step of the fade has to be inverted. */
void checkFade(){
  	analogWrite(LED_WRONG, fade_amount);
    fade_amount += step;
	if (fade_amount <= 0 || fade_amount >= 255) {
      step = -step;
    }
}

/* 
	Checks if the game needs to be started, 
	so if the player pushed the B1 button.
*/
void checkGameStarted(){
  if (digitalRead(btns[0]) == HIGH) {
      game_started = 1;
      digitalWrite(LED_WRONG, LOW);
      nextTurn();
    }
}

void loop() {
  if (game_started == 0) {
    checkFade();
    checkGameStarted();
  } else {
    int i;
    for (i = 0; i < LED_N; i++) {
      if (is_button_state_high(BTN_1)) {
        if (get_led_state(i) == LOW) {
          set_led_state(i,HIGH);
          curr_bin += bin_vals[i];
        } else {
          set_led_state(i,LOW);
          curr_bin -= bin_vals[i];
        }
        Serial.println(curr_bin);
      }
    }
  }
  delay(LOOP_DELAY_MS);
}