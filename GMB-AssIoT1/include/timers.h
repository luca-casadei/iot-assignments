/*
    It is the starting time of the game.
*/
#define START_TIME_SEC 60UL

/*
    It is the time that the game will sleep during the blinking state.
*/
#define GOTO_SLEEP_TIME 10UL

/*
    It is the minimum time that the game will have.
*/
#define MIN_TIME_VAL 20UL

/*
    It is a multiplier to convert seconds to microseconds.
*/
#define MICRO_MUL 1000000UL

/*
    It is the factor that will be multiplied by the difficulty.
*/
#define F_FACTOR 2UL

/*
    Sets up the timer with the sleeping time in the setup.
*/
void initialize_timerone(void);

/*
    Stops the timer that ends the rounds.
*/
void detach_timerone(void);

/*
    Starts the timer that ends the rounds.
*/
void go_to_sleep(void);

/*
    Sets up the timer with the sleeping time.
*/
void set_sleep_timer(void);

/*
    Sets up the timer with the game time.
*/
void set_game_timer(void);