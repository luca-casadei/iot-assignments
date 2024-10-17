/*
    Sets up the timer with the sleeping time in the setup.
*/
void set_game_timer(long difficulty);
void reset_game_timer(void);

/*
    Starts the timer that ends the rounds.
*/
void set_sleep_timer(void);

/*
    Sets up the timer with the sleeping time.
*/
void check_sleep_timer(void);

/*
    Sets up the timer with the game time.
*/
void check_game_timer(void);

/*
 * Checks if the red LED can be faded in the loop.
 */
bool check_fade_timer(void);

/*
    It is a delay function that uses millis.
*/
void delay_millis(unsigned long time_millis);