/*
  Luca Casadei
  Francesco Pazzaglia
*/

#include <Arduino.h>
#include "game.h"
#include "leds.h"

#define GAME_OVER_DELAY 5000

void setup()
{
  Serial.begin(9600);
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
    enum round_state r = round_won();
    if (r == WON)
    {
      next_turn();
    }
    else if (r == LOST)
    {
      shut_leds();
      set_analog_red_led(255);
      delay(GAME_OVER_DELAY);
      set_analog_red_led(LOW);
      game_blink();
    }
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

  delay(20);
}