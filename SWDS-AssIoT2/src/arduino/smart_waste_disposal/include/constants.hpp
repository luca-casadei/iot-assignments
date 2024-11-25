#pragma once
/**
 * PINS
 */
#define SERVO_PIN 10
#define GREEN_PIN 2
#define RED_PIN 3
#define MOTION_DETECTOR A3

/**
 * LCD
 */
#define LCD_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

/**
 * Serial
 */
#define BAUD 9600UL
#define SEPARATOR ('\n')

/**
 * Tasks
 */
#define SCHEDULER_MCD_PERIOD 50U
#define TASK_SLEEP_PERIOD 500U