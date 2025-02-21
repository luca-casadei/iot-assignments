#pragma once

#include "constants.hpp"
#include "HWPlatform.hpp"

enum SystemState
{
  AUTOMATIC,
  MANUAL
};

class UserPanel {

public:
  UserPanel(HWPlatform* pHW);

  void init();

  void turnOffDisplay();
  void turnOnDisplay();

  SystemState selectedMode();

  int getWindowOpeningPercentage();

  void sync();

private:
  LCD* pLcd; 
  Button* pButtonMode;
  ServoMotor* pWindow;
  SystemState actualMode;
};
