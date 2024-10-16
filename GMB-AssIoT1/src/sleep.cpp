#include <avr/sleep.h>
#include <avr/power.h>
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
    power_adc_disable();
    power_twi_disable();
    power_spi_disable();
    power_timer0_disable();
    power_timer2_disable();
    disable_interrupt_to(BTN_1);
    enable_interrupt_to(BTN_1, wake_up);
    enable_interrupt_to(BTN_2, wake_up);
    enable_interrupt_to(BTN_3, wake_up);
    enable_interrupt_to(BTN_4, wake_up);
    sleep_mode();
    sleep_disable();
    power_all_enable();
}