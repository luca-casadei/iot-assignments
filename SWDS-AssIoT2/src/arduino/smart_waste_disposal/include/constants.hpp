#pragma once
/**
 * PINS
 */
#define SERVO_PIN 10
#define GREEN_PIN 2
#define RED_PIN 3
#define MOTION_DETECTOR A3
#define ECHO 6
#define TRIG 7
#define MAX_RECV_TIME 5U
#define MAX_ENT_TIME 5U
#define TRASHTRESH_CM 5
#define MAX_EMPTY_TIME 10U

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
#define SEPARATOR ('\n')

/**
 * Temperature Sensor
 */
#define TEMPERATURE_THRESHOLD 26
#define TEMPERATURE_SENSOR A2
#define MAX_TEMP_TIME 5U

/**
 * Task Periods
 */
#define SCHEDULER_MCD_PERIOD 50U
#define TASK_SLEEP_PERIOD 500U
#define TASK_TEMP_PERIOD 100U
#define TASK_WASTE_PERIOD 100U
