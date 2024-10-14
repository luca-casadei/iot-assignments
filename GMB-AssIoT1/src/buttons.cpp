#include <Arduino.h>
#include "pins.h"
#include "buttons.h"

void initialize_buttons(void)
{
    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);
    pinMode(BTN_4, INPUT);
}
