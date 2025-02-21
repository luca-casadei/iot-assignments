#pragma once

#include "servo_motor.hpp"
#include <Arduino.h>
#include <ServoTimer2.h>

class ServoMotorImpl: public ServoMotor {

public:
  ServoMotorImpl(int pin);

  void on();
  bool isOn();
  void setPosition(int angle);
  int getPosition();
  void off();
    
private:
  int pin; 
  bool _on;
  ServoTimer2 motor;
  int lastAngle;
};
