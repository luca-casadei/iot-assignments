#include <Arduino.h>
#include "potentiometer.h"
#include "pins.h"

/*
 * Uncomment this line to see difficulty print.
 */
/*#define DEBUG*/

void initialize_potentiometer(void)
{
  pinMode(POTENTIOMETER, INPUT);
}

long choose_difficulty(void)
{
  int potentiometer_value = analogRead(POTENTIOMETER);
  long chosen_diff = map(potentiometer_value, 0, 1023, 1, 4);
#ifdef DEBUG
  Serial.print("Chosen difficulty: ");
  Serial.println(chosen_diff);
#endif
  return chosen_diff;
}