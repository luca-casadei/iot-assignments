#define START_TIME_SEC 60UL
#define MICRO_MUL 1000000UL
#define GOTO_SLEEP_TIME 10UL
#define F_FACTOR 2UL
#define MIN_TIME_VAL 20UL


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