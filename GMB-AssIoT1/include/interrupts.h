/*
    Enable/Disable interrupt for the button pin.
    Default button pin is for BTN 1.
*/
void enable_interrupt_to(unsigned char button_pin);
void disable_interrupt_to(unsigned char button_pin);
/*
    Get the button pin that triggered the interrupt.
*/
unsigned char get_for_execution(void);
/*
    Init the button pin that triggered the interrupt.
*/
void initialize_interrupts(void);
/*
    Sleep timer elapsed interrupt.
*/
void sleep_timer_elapsed(void);

void game_timer_elapsed(void);

/*
    Attach a function to a pin.
*/
void attach_to_function(unsigned char pin, void (*f)(void));