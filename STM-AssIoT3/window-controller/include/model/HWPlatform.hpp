#pragma once

#include <Wire.h> 
#include "constants.hpp"
#include "devices/Button.hpp"
#include "devices/servo_motor.hpp"
#include "devices/LCD.hpp"
#include "devices/Potentiometer.hpp"

// LCD define
#define LCD_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

class HWPlatform {

public:
  HWPlatform();
  void init();

  Button* getModeButton();
  LCD* getUserPanelLcd(); 
  ServoMotor* getWindowMotor();
  Potentiometer* getPotentiometer();

private:
  Button* pButtonMode;
  LCD* pLcd; 
  ServoMotor* pMotorWindow;
  Potentiometer* pPotentiometer;

};
