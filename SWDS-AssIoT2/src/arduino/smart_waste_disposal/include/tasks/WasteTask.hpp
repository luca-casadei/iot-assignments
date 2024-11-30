#pragma once
#include "TaskWithCounter.hpp"

class Led;
class Button;
class WasteSensor;
class TemperatureTask;
class LCD;
class ServoMotor;

class WasteTask : public TaskWithCounter
{
private:
  unsigned int counter;
  Led * green_led;
  Led * red_led;
  Button * open_button;
  Button * close_button;
  WasteSensor * waste_sensor;
  TemperatureTask * tTask;
  ServoMotor * servo;
  LCD * lcd;
  unsigned int waste_max_level; 
  enum State{
      CLOSED,
      OPEN,
      RECEIVED,
      ERRORED,
      FULL,
      EMPTYING
  } state;
  void to_received();
  void to_closed();
  void to_full();
  void to_open();
  void to_emptying();
  void to_errored();
    
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
                    unsigned int waste_max_level,
                    unsigned int door_pin,
                    TemperatureTask * tTask,
                    LCD * lcd);
  void init(unsigned int period) final;
  double get_fullness();
  void tick() final;
};
