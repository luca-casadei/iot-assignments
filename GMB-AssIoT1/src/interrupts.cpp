#include <EnableInterrupt.h>
#include "interrupts.h"

void enable_interrupt_to(unsigned char button_pin, void (*function)()){
    disableInterrupt(button_pin);
    enableInterrupt(button_pin, function, RISING);
}

void disable_interrupt_to(unsigned char button_pin){
    disableInterrupt(button_pin);
}
