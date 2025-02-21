#pragma once

#include "constants.hpp"
#include "HWPlatform.hpp"

enum SystemMode
{
  AUTOMATIC,
  MANUAL
};

class UserPanel
{

public:
  UserPanel(HWPlatform *pHW);

  void init();

  void turnOffDisplay();
  void turnOnDisplay();
  void printToLine(const int line, const char *msg);

  void setSystemMode(const SystemMode mode);
  SystemMode getSystemMode();

  int getWindowOpeningPercentage();

  void sync();

private:
  LCD *pLcd;
  Button *pButtonMode;
  ServoMotor *pWindow;
  SystemMode actualMode;
};
