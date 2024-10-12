#define START_TIME_SEC 20UL
#define MICRO_MUL 1000000UL
#define GOTO_SLEEP_TIME 10UL
#define F_FACTOR 2UL
#define MIN_TIME_VAL 10UL

/*
    It initializes the timer for the sleep mode.
*/
void initialize_sleep_timer(void);

/*
    It stops the timer for the sleep mode.
*/
void stop_sleep_timer(void);

/*
    Starts the timer tha ends the rounds.
*/
void initialize_game_over_timer(void);

/*
    Stops the timer that ends the rounds.
*/
void detach_timer(void);