#include <avr/sleep.h>
#include "pins.h"
#include "interrupts.h"

void wake_up(void) {}

void go_to_sleep(void)
{
#ifdef DEBUG
    Serial.println("Entering a deep sleep...");
#endif
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    disable_interrupt_to(BTN_1);
    attach_to_function(BTN_1,wake_up);
    attach_to_function(BTN_2,wake_up);
    attach_to_function(BTN_3,wake_up);
    attach_to_function(BTN_4,wake_up);
    sleep_mode();
    sleep_disable();
}