#include "./model/UserPanel.hpp"
#include <Arduino.h>
#include "constants.hpp"
#include "model/HWPlatform.hpp"

UserPanel::UserPanel(HWPlatform *pHW)
{
  this->pLcd = pHW->getUserPanelLcd();
  this->pButtonMode = pHW->getModeButton();
  this->pWindow = pHW->getWindowMotor();
  this->pPotentiometer = pHW->getPotentiometer();
}

void UserPanel::init()
{
  pLcd->init();
  turnOnDisplay();
  pWindow->on();
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
  const int cappedPos = constrain(position, 1, 99);
  const int anglePos = map(cappedPos, 1, 99, 0, 180);
  this->pWindow->setPosition(anglePos);
}

int UserPanel::getWindowOpeningPercentage()
{
  return this->pWindow->getPosition();
}

int UserPanel::getPotentiometerValue() 
{
  return this->pPotentiometer->getValue();
}

bool UserPanel::isButtonModePressed()
{
  return pButtonMode->isPressed();
}

void UserPanel::sync()
{
  pButtonMode->sync();
}
