#pragma once
/**
 * Times (seconds)
 */
#define MAX_RECV_TIME 5U  // T2
#define MAX_ENT_TIME 5U   // T1
#define MAX_EMPTY_TIME 6U // T3

/**
 * Leds
 */
#define GREEN_PIN 2
#define RED_PIN 3

/**
 * PIR
 */
#define MOTION_DETECTOR A3

/**
 * WasteDetector (Sonar)
 */
#define ECHO 6
#define TRIG 7
#define TRASHTRESH_CM 3

/**
 * LCD
 */
#define LCD_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

/**
 * Buttons
 */
#define OPEN_PIN 13
#define CLOSE_PIN 12

/**
 * Serial
 */
#define BAUD 9600UL

/**
 * ServoMotor
 */
#define SERVO_PIN 10

/**
 * Temperature Sensor
 */
#define TEMPERATURE_THRESHOLD 30
#define TEMPERATURE_SENSOR A2
#define MAX_TEMP_TIME 5U

/**
 * Task Periods
 */
#define SCHEDULER_MCD_PERIOD 50U
#define TASK_SLEEP_PERIOD 150U
#define TASK_TEMP_PERIOD 100U
#define TASK_WASTE_PERIOD 100U
