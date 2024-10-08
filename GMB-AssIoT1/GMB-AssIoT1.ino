/*
	Luca Casadei
  Francesco Pazzaglia
  Lucio Baiocchi
*/

#include <TimerOne.h>

#define BTN_1 12
#define BTN_2 3
#define BTN_3 4
#define BTN_4 5

#define BTN_LED_N 4


#define START_TIME_SEC 10

#define MICRO_MUL 1000000

#define LOOP_DELAY_MS 100
#define GAMEOVER_DELAY_MS 1000

unsigned int btns[BTN_LED_N] = { BTN_1, BTN_2, BTN_3, BTN_4 };
unsigned int leds[BTN_LED_N] = { LED_1, LED_2, LED_3, LED_4 };
unsigned int bin_vals[BTN_LED_N] = { 8, 4, 2, 1 };
unsigned short states[BTN_LED_N] = { LOW, LOW, LOW, LOW };

/* Game values */
unsigned int curr_bin;
unsigned int score;
unsigned int time_us;
unsigned short correct_answer;
unsigned int game_started;

void nextTurn() {
  curr_bin = 0;
  /* Sets the value to be converted in binary */
  randomSeed(micros());
  correct_answer = random(0, 15);
  shutLeds(leds);
  
  /* TODO: Decrease time on next turn */
  unsigned int pot_f = analogRead(A5) / 255;
  unsigned int f_factor = ((pot_f * 5) / 3);
  time_us = (time_us - f_factor);

  /* Sets the timer for game over */
  Serial.print("Tempo: ");
  Serial.print(time_us);
  Serial.println();
  Timer1.initialize(time_us * MICRO_MUL);
  Timer1.attachInterrupt(timesUpHandler);
}

void timesUpHandler() {
  Serial.print("Risposta: ");
  Serial.print(curr_bin, DEC);
  Serial.println();
  Serial.print("Risposta corretta: ");
  Serial.print(correct_answer, DEC);
  Serial.println();
  if (correct_answer == curr_bin) {
    score += 1;
    nextTurn();
  } else {
    digitalWrite(LED_WRONG, HIGH);
    shutLeds(leds);
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

  /* Zeroes the player's score */
  score = 0;
  curr_bin = 0;


  /* Activates Arduino's pins */
  int i;
  for (i = 0; i < BTN_LED_N; i++) {
    pinMode(btns[i], INPUT);
    pinMode(leds[i], OUTPUT);
  }
  pinMode(LED_WRONG, OUTPUT);
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
    for (i = 0; i < BTN_LED_N; i++) {
      if (digitalRead(btns[i]) == HIGH) {
        if (states[i] == LOW) {
          digitalWrite(leds[i], HIGH);
          states[i] = HIGH;
          curr_bin += bin_vals[i];
        } else {
          states[i] = LOW;
          curr_bin -= bin_vals[i];
        }
        Serial.println(curr_bin);
        digitalWrite(leds[i], states[i]);
      }
    }
  }
  delay(LOOP_DELAY_MS);
}