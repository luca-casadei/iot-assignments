#include "leds.h"

void shutLeds(unsigned int * leds) {
  int i;
  for (i = 0; i < (sizeof(leds) / sizeof(leds[0])); i++) {
    digitalWrite(leds[i], LOW);
    states[i] = LOW;
  }
}
