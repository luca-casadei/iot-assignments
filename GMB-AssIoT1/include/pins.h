/* 
 * Four corresponding button pins 
 */
#define BTN_1 2
#define BTN_2 3
#define BTN_3 4
#define BTN_4 5

/* 
 * Four green LED pins.
 */
#define LED_1 8
#define LED_2 9
#define LED_3 10
#define LED_4 11

/* 
 * The pin of fading and game over red LED. 
 */
#define LED_WRONG 6

/* 
 * Potentiometer PIN 
 */
#define POTENTIOMETER A0

/* 
 * Timer constants, used for interrupts.
 */
#define TIME_GAME_OVER 100
#define TIME_TO_SLEEP 101

/* 
 * Timer constants used for specify that are no interrupts in queue. 
 */
#define NOINT 255