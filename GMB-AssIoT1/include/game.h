/* 
  Gets the binary value of the current pressed buttons in sum. 
*/
unsigned short get_current_binary_value(void);

/* 
  Gets the associated binary values. 
*/
unsigned short *get_bin_vals(void);

/* 
  Increses the chosen binary values. 
*/
void increase_curr_bin_amount(unsigned int amount_index, bool increase);

/* 
  Sets the game values to the defaults. 
*/
void initialize_game(void);

/* 
  Gets the current player's score 
*/
unsigned int get_score(void);

/* 
  Adds 1 to the current player's score. 
*/
void increment_score(void);

/* 
  Checks if the current guessed value is the same as the correct one. 
*/
bool round_won(void);

/*
  Checks if the current player has won the game. 
*/
void next_turn(void);

/*
  Game states
*/
void game_start(void);
void game_sleep(void);
void game_blink(void);

/*
    Game state enum
*/
enum game_state
{
    BLINKING,
    SLEEPING,
    RUNNING
};

/*
    Gets the current game state.
*/
enum game_state get_game_state(void);