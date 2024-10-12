/* 
    Enable/Disable interrupt for the button pin.
    Default button pin is for BTN 1.
*/
void enable_interrupt_to(void (*function)());
void enable_interrupt_to(unsigned char button_pin, void (*function)());
void disable_interrupt_to(unsigned char button_pin);