#pragma once

class ServoMotor;
class Button;
class LCD;
class Potentiometer;

class UserPanel
{

public:
  UserPanel();

  void init();

  void turnOffDisplay();
  void turnOnDisplay();
  void printToLine(const int line, const char *msg);

  bool isButtonModePressed();

  void saveTemperature(const float temp);
  float getTemperature();

  void setWindowPosition(const int position);
  int getWindowOpeningPercentage();

  int getPotentiometerValue();

  void sync();

private:
  LCD *pLcd;
  Button *pButtonMode;
  ServoMotor *pWindow;
  Potentiometer *pPotentiometer;
  float currentTemperature;
};
