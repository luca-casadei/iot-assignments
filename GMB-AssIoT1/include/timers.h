/*
    It is the starting time of the game.
*/
#define START_TIME_SEC 10UL

/*
    It is the time that the game will sleep during the blinking state.
*/
#define GO_TO_SLEEP_TIME 10UL

/*
    It is the minimum time that the game will have.
*/
#define MIN_TIME_VAL 20UL

/*
    It is a multiplier to convert seconds to microseconds.
*/
#define MILLIS_MUL 1000UL

/*
    It is the factor that will be multiplied by the difficulty.
*/
#define F_FACTOR 2UL

/*
    Sets up the timer with the sleeping time in the setup.
*/
void set_game_timer(void);

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
    It is a delay function that uses millis.
*/
void delay_millis(unsigned long time_millis);