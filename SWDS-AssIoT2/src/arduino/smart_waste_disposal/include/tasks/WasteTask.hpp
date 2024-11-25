#pragma once
#include "TaskWithCounter.hpp"

class Led;
class Button;
class WasteSensor;

class WasteTask : public TaskWithCounter
{
private:
  unsigned int counter;
  Led * green_led;
  Led * red_led;
  Button * open_button;
  Button * close_button;
  WasteSensor * waste_sensor;
  unsigned int max_entered_waste_time; // T1 
  unsigned int waste_received_time; // T2
  unsigned int waste_emptying_time; // T3
  unsigned int waste_max_level; 
  enum State{
      CLOSED,
      OPEN,
      RECEIVED,
      ERRORED,
      FULL,
      EMPTYING
  } state;
    
public:
  WasteTask(unsigned int green_led_pin,
                    unsigned int red_led_pin,
                    unsigned int open_button_pin, 
                    unsigned int close_button_pin, 
                    unsigned int waste_sensor_echo_pin, 
                    unsigned int waste_sensor_trig_pin, 
                    unsigned int max_entered_waste_time, 
                    unsigned int waste_received_time, 
                    unsigned int waste_emptying_time,
                    unsigned int waste_max_level);
  void init(unsigned int period) final;
  void tick() final;
};
