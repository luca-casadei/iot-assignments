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
  this->pWindow->setPosition(position);
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
