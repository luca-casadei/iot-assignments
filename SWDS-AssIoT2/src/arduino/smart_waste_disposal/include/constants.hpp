#pragma once
/**
 * PINS
 */
#define SERVO_PIN 10
#define LCD_ADDR 0x27
#define GREEN_PIN 2
#define RED_PIN 3
#define MOTION_DETECTOR A5

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