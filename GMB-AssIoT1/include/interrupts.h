/*
    Enables interrupt for the button pin.
*/
void enable_interrupt_to(unsigned char button_pin);
void enable_interrupt_to(unsigned char pin, void (*f)(void));

/*
    Disables interrupt for the button pin.
*/
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

/*
    Game timer elapsed interrupt.
*/
void game_timer_elapsed(void);
