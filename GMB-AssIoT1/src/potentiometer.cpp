#include <Arduino.h>
#include "potentiometer.h"

void initialize_potentiometer(void) {
  pinMode(POTENTIOMETER, INPUT);
}