#define DEBUG

/*
  Luca Casadei
  Francesco Pazzaglia
*/

#include <Arduino.h>
#include "game.h"
#include "buttons.h"
#include "potentiometer.h"
#include "leds.h"

void setup()
{
  Serial.begin(9600);

  /* Activates Arduino's pins */
  initialize_buttons();
  initialize_potentiometer();
  initialize_leds();
  initialize_game();
}

void loop()
{
  switch (get_game_state())
  {
  case BLINKING:
  {
#ifdef DEBUG
    Serial.println("State: Blink");
#endif
    fade();
    break;
  }

  case RUNNING:
  {
#ifdef DEBUG
    Serial.println("State: Running");
#endif
    break;
  }

  case SLEEPING:
  {
#ifdef DEBUG
    Serial.println("State: Sleeping");
#endif
    break;
  }

  default:
    break;
  }

  delay(BOUNCING_PREVENTION_TIME);
}