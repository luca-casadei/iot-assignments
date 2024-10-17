/* 
  The main game state, used to correctly manage interrupts. 
*/
typedef enum game_state
{
  RUNNING,
  BLINKING,
  SLEEPING
} GameState;

/*
 * Initializes the game.
 */
void initialize_game(void);

/*
 * Gets the current game state.
 */
GameState get_game_state();

/*
 * Sets the game blinking state.
 */
void game_blink(void);

/*
 * Sets the game sleeping state.
 */
void game_sleep(void);

/*
 * Sets the game running state.
 */
void game_run(void);

/*
 * Returns true if the lit LEDs binary sum is equal to the correct random decimal value.
 */
bool game_won(void);

/*
 * Resets the values to be able to play a new round.
 */
void next_round(void);

/*
 * Toggles the binary state (subtracts if already lit, adds otherwise).
 */
void toggle_binary(unsigned short index);

/*
 * Returns the current player's score.
 */
unsigned short get_score();

/*
 * Returns the correct value of the current round.
 */
unsigned short get_correct_value();