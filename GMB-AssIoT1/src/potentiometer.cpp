#include <Arduino.h>
#include "potentiometer.h"

void initialize_potentiometer(void) {
  pinMode(POTENTIOMETER, INPUT);
}

long choose_difficulty(void) {
  int potentiometer_value = analogRead(POTENTIOMETER);
  return map(potentiometer_value, 0, 1023, 1, 4);
}