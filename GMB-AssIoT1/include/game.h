/* Gets the binary value of the current pressed buttons in sum. */
unsigned short get_current_binary_value(void);
/* Gets the associated binary values. */
unsigned short * get_bin_vals(void);
/* Increses the chosen binary values. */
void increase_curr_bin_amount(short amount);
/* Sets the game values to the defaults. */
void initialize_game(void);
/* Gets the current player's score */
unsigned int get_score(void);
/* Adds 1 to the current player's score. */
void increment_score(void);
/* Checks if the current guessed value is the same as the correct one. */
bool round_won(void);