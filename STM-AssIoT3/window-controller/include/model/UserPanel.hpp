#pragma once

#include "constants.hpp"
#include "HWPlatform.hpp"

class UserPanel
{

public:
  UserPanel(HWPlatform *pHW);

  void init();

  void turnOffDisplay();
  void turnOnDisplay();
  void printToLine(const int line, const char *msg);

  bool isButtonModePressed();

  void saveTemperature(const float temp);
  float getTemperature();

  void setWindowPosition(const int position);
  int getWindowOpeningPercentage();

  void sync();

private:
  LCD *pLcd;
  Button *pButtonMode;
  ServoMotor *pWindow;
  Potentiometer *pPotentiometer;
  float currentTemperature;
};
