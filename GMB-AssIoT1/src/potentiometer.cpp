#include <Arduino.h>
#include "potentiometer.h"
#include "pins.h"

/*
 * Uncomment this line to see difficulty prints.
 */
// #define DEBUG

void initialize_potentiometer(void)
{
  pinMode(POTENTIOMETER, INPUT);
}

long choose_difficulty(void)
{
  int potentiometer_value = analogRead(POTENTIOMETER);
#ifdef DEBUG
  Serial.print("Analog potentiometer value: ");
  Serial.println(potentiometer_value);
#endif
  /* To avoid noise-induced unstable readings. */
  potentiometer_value = constrain(potentiometer_value, 8, 1015);
  long chosen_diff = map(potentiometer_value, 8, 1015, 1, 4);
#ifdef DEBUG
  Serial.print("Chosen difficulty: ");
  Serial.println(chosen_diff);
#endif
  return chosen_diff;
}