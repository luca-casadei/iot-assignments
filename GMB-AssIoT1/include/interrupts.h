/*
 * Enables interrupt for the button pin(optionally with a specific function).
 */
void enable_interrupt_to(unsigned char button_pin);
void enable_interrupt_to(unsigned char pin, void (*f)(void));

/*
 * Disables interrupt for the button pin.
 */
void disable_interrupt_to(unsigned char button_pin);

/*
 * Gets the sender that triggers the interrupt.
 */
unsigned char get_for_execution(void);

/*
 * Initializes the "queue of interrupts" and enqueues the BTN 1.
 */
void initialize_interrupts(void);

/*
 * Enqueues the sleep timer.
 */
void sleep_timer_elapsed(void);

/*
 * Enqueues the game over timer.
 */
void game_timer_elapsed(void);
