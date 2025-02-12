#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "pins.hpp"
#include "devices/Button.hpp"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "devices/servo_motor.hpp"

class HWPlatform {

public:
  HWPlatform();
  void init();
  void test();

  Button* getModeButton();
  LiquidCrystal_I2C* getUserPanelLcd(); 
  ServoMotor* getWindowMotor();

private:
  Button* pButtonMode;
  LiquidCrystal_I2C* pLcd; 
  ServoMotor* pMotorWindow;

};

#endif
