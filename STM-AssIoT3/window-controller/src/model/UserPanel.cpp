#include <Arduino.h>
#include "constants.hpp"
#include "./model/UserPanel.hpp"
#include "./devices/LCD.hpp"
#include "./devices/ButtonImpl.hpp"
#include "./devices/Potentiometer.hpp"
#include "./devices/servo_motor_impl.hpp"

UserPanel::UserPanel()
{
  this->pLcd = new LCD(LCD_ADDR, LCD_COLS, LCD_ROWS);
  this->pButtonMode = new ButtonImpl(BUTTON_MODE_PIN);
  this->pPotentiometer = new Potentiometer(POTENTIOMETER_PIN);
  this->pWindow = new ServoMotorImpl(MOTOR_PIN);
}

void UserPanel::init()
{
  pLcd->init();
  turnOnDisplay();
  pWindow->on();
  setOldPotValue(getPotentiometerValue());
}

void UserPanel::turnOnDisplay()
{
  pLcd->on();
}

void UserPanel::turnOffDisplay()
{
  pLcd->off();
}

void UserPanel::printToLine(const int line, const char *msg)
{
  pLcd->printToLine(line, msg);
}

void UserPanel::saveTemperature(const float temp)
{
  currentTemperature = temp;
}

float UserPanel::getTemperature()
{
  return currentTemperature;
}

void UserPanel::setWindowPosition(const int position)
{
  const int cappedPos = constrain(position, 0, 100);
  this->currentPercentage = cappedPos;
  const int anglePos = map(cappedPos, 0, 100, 0, 180);
  this->pWindow->setPosition(anglePos);
}

int UserPanel::getOldPotValue(){
  return this->oldPotValue;
}

void UserPanel::setOldPotValue(int opv){
  this->oldPotValue = opv;
}

int UserPanel::getWindowOpeningPercentage()
{
  return this->currentPercentage;
}

int UserPanel::getPotentiometerValue() 
{
  return this->pPotentiometer->getValue();
}

void UserPanel::setDashboardPercentage(int dp){
  this->dashBoardPercentage = dp;
}

int UserPanel::getDashboardPercentage(){
  return this->dashBoardPercentage;
}

bool UserPanel::isButtonModePressed()
{
  return pButtonMode->isPressed();
}

void UserPanel::sync()
{
  pButtonMode->sync();
  pPotentiometer->sync();
}
