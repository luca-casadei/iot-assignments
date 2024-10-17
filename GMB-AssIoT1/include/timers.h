/*
 * Sets up the game over timer with the game over time.
 */
void set_game_timer(long difficulty);

/*
 * Resets the game over timer.
 */
void reset_game_timer(void);

/*
 * Starts the sleep timer.
 */
void set_sleep_timer(void);

/*
 * Checks if the sleep timer has finished.
 */
void check_sleep_timer(void);

/*
 * Checks if the game over timer has finished.
 */
void check_game_timer(void);

/*
 * Checks if the red LED can be faded in the loop.
 */
bool check_fade_timer(void);

/*
 * It is a delay function that uses milliseconds.
 */
void delay_millis(unsigned long time_millis);