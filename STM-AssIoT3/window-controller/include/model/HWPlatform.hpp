#pragma once

#include "constants.hpp"
#include "devices/Button.hpp"
#include <Wire.h> 
#include "devices/servo_motor.hpp"
#include "devices/LCD.hpp"

// LCD define
#define LCD_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

class HWPlatform {

public:
  HWPlatform();
  void init();
  void test();

  Button* getModeButton();
  LCD* getUserPanelLcd(); 
  ServoMotor* getWindowMotor();

private:
  Button* pButtonMode;
  LCD* pLcd; 
  ServoMotor* pMotorWindow;

};
