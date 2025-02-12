#ifndef __USER_PANEL__
#define __USER_PANEL__

#include "pins.hpp"
#include "HWPlatform.hpp"
#include <LiquidCrystal_I2C.h>

class UserPanel {

public:
  UserPanel(HWPlatform* pHW);

  void init();

  void turnOffDisplay();
  void turnOnDisplay();
  
  bool pressedOpen();
  bool pressedClose();

  void sync();

 private:
  LiquidCrystal_I2C* pLcd; 
  Button* pButtonMode;
  bool modePressed;
};

#endif
