#pragma once

#include "pins.hpp"
#include "HWPlatform.hpp"

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
  LCD* pLcd; 
  Button* pButtonMode;
  bool modePressed;
};
