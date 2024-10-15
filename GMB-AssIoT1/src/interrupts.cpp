#define DEBUG

#include <EnableInterrupt.h>
#include <pinqueue.h>
#include "interrupts.h"
#include "pins.h"

#define INTN 6

static void add_to_queue(unsigned char interrupt_emitter)
{
    static unsigned long last_interrupt_time = 0;
    unsigned long current_time = millis();

    if (interrupt_emitter == TIME_GAME_OVER || interrupt_emitter == TIME_TO_SLEEP)
    {
        queue_empty();
        enqueue(interrupt_emitter);
    }
    else
    {
        /* Debouncing check */
        if ((current_time - last_interrupt_time) >= 100)
        {
            last_interrupt_time = current_time;
            enqueue(interrupt_emitter);
        }
    }
}

static void button1_pressed(void)
{
    add_to_queue(BTN_1);
}

static void button2_pressed(void)
{
    add_to_queue(BTN_2);
}

static void button3_pressed(void)
{
    add_to_queue(BTN_3);
}

static void button4_pressed(void)
{
    add_to_queue(BTN_4);
}

void sleep_timer_elapsed(void){
    add_to_queue(TIME_TO_SLEEP);
}

void game_timer_elapsed(void){
    add_to_queue(TIME_GAME_OVER);
}

unsigned char get_for_execution(void)
{
    unsigned char val = peek();
    dequeue();
    return val;
}

void enable_interrupt_to(unsigned char pin)
{
    void (*f)(void);
    switch (pin)
    {
    case BTN_1:
    {
        f = button1_pressed;
        break;
    }
    case BTN_2:
    {
        f = button2_pressed;
        break;
    }
    case BTN_3:
    {
        f = button3_pressed;
        break;
    }
    case BTN_4:
    {
        f = button4_pressed;
        break;
    }
    default:
        break;
    }
    enableInterrupt(pin, f, RISING);
}

void enable_interrupt_to(unsigned char pin, void (*f)(void))
{
    enableInterrupt(pin, f, RISING);
}

void disable_interrupt_to(unsigned char button_pin)
{
    disableInterrupt(button_pin);
}

void initialize_interrupts(void)
{
    queue_init(INTN);
    enable_interrupt_to(BTN_1);
}