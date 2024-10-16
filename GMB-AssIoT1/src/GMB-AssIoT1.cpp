/*
 * Embedded and IoT 2024-2025
 * Assignment n.1 by
 * Luca Casadei
 * Francesco Pazzaglia
 */

#include <Arduino.h>
#include "game.h"
#include "buttons.h"
#include "leds.h"
#include "potentiometer.h"
#include "interrupts.h"
#include "timers.h"
#include "pins.h"
#include "lcd.h"
#include "sleep.h"

/* Comment this lines to hide prints. */
#define DEBUG
//#define DEBUG_VERBOSE

static volatile bool first_entered;

void setup()
{
  /* Serial line */
  Serial.begin(9600);

  /* Initialization */
  initialize_game();
  initialize_buttons();
  initialize_leds();
  initialize_potentiometer();
  initialize_interrupts();
  initialize_lcd();
  first_entered = true;
}

void loop()
{
  unsigned char interrupt_provider = get_for_execution();
  switch (get_game_state())
  {
    /*
     * When the game is in the blinking state
     * we will handle only the interrupts present
     * in this switch case.
     */
  case BLINKING:
  {
    if (first_entered)
    {
      lcd_wakeup();
      set_sleep_timer();
      print_second_line("Welcome to GMB!");
      print_third_line("Press B1 to Start");
      first_entered = false;
    }
    check_sleep_timer();
    switch (interrupt_provider)
    {
      /*
       * If the firt button is pressed while we are
       * in the blinking state, we set the game into
       * running mode, the interrupts on the last three
       * button will be enabled and we'll be ready to
       * play.
       */
    case BTN_1:
    {
      game_run();
      first_entered = true;
      enable_interrupt_to(BTN_2);
      enable_interrupt_to(BTN_3);
      enable_interrupt_to(BTN_4);
      break;
    }
    /*
     * When the sleep timer elapses, this case will be called
     * so the red LED will be set to LOW and the sleep mode
     * will be started.
     */
    case TIME_TO_SLEEP:
    {
      set_analog_red_led(LOW);
      lcd_shutdown();
      game_sleep();
      go_to_sleep();
      break;
    }
    default:
      break;
    }
    fade();
#ifdef DEBUG_VERBOSE
    Serial.println("State: Blinking");
#endif
    break;
  }
    /*
     * The actual gaming phase, no phase here every
     * button interrupt will be activated, and the timer
     * one will have the game over time to count down.
     */
  case RUNNING:
  {
    if (first_entered == true)
    {
      print_second_line("Go!");
      empty_line(INIT_LCD_COL, 2);
      delay_millis(1000);
      set_game_timer();
      set_analog_red_led(LOW);
      char *s = (char *)malloc(sizeof(char) * LCD_COLUMNS);
      sprintf(s, "%hu", get_correct_value());
      print_second_line(s);
#ifdef DEBUG
      Serial.println(s);
#endif
      sprintf(s, "Score: %hu", get_score());
      print_third_line(s);
      free(s);
      first_entered = false;
    }
    check_game_timer();
    /*
     * This switch checks for the pressed
     * button and increases/decreases the
     * corresponding value.
     */
    switch (interrupt_provider)
    {
    case BTN_1:
    {
      toggle_binary(0);
      set_led_state(0);
      break;
    }
    case BTN_2:
    {
      toggle_binary(1);
      set_led_state(1);
      break;
    }
    case BTN_3:
    {
      toggle_binary(2);
      set_led_state(2);
      break;
    }
    case BTN_4:
    {
      toggle_binary(3);
      set_led_state(3);
      break;
    }
    case TIME_GAME_OVER:
    {
      shut_leds();
#ifdef DEBUG
      Serial.print("Correct value: ");
      Serial.println(get_correct_value());
#endif
      if (game_won())
      {
#ifdef DEBUG
        Serial.println("You won!");
#endif
        print_second_line("GOOD!");
        char *s = (char *)malloc(sizeof(char) * LCD_COLUMNS);
        sprintf(s, "Score: %hu", get_score());
        print_third_line(s);
        free(s);
        delay_millis(1000);
        next_round();
        first_entered = true;
      }
      else
      {
        print_second_line("Game Over!");
        char *s = (char *)malloc(sizeof(char) * LCD_COLUMNS);
        sprintf(s, "Final Score: %hu", get_score());
        print_third_line(s);
        free(s);
        set_analog_red_led(255);
        delay_millis(1000);
        set_analog_red_led(LOW);
        first_entered = true;
        game_blink();
        disable_interrupt_to(BTN_2);
        disable_interrupt_to(BTN_3);
        disable_interrupt_to(BTN_4);
      }
      break;
    }
    default:
      break;
    }
#ifdef DEBUG_VERBOSE
    Serial.println("State: Running");
#endif
    break;
  }

  case SLEEPING:
  {
#ifdef DEBUG_VERBOSE
    Serial.println("State: Sleeping");
#endif
    game_blink();
    first_entered = true;
    disable_interrupt_to(BTN_1);
    disable_interrupt_to(BTN_2);
    disable_interrupt_to(BTN_3);
    disable_interrupt_to(BTN_4);
    enable_interrupt_to(BTN_1);
    break;
  }

  default:
    break;
  }

#ifdef DEBUG
  if (interrupt_provider != NOINT)
  {
    Serial.print("Executed interrupt: ");
    Serial.print(interrupt_provider);
    Serial.println();
  }
#endif
}