#include "./model/UserPanel.hpp"
#include <Arduino.h>
#include "constants.hpp"
#include "model/HWPlatform.hpp"

UserPanel::UserPanel(HWPlatform *pHW)
{
  pLcd = pHW->getUserPanelLcd();
  pButtonMode = pHW->getModeButton();
  pWindow = pHW->getWindowMotor();
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
  return pWindow->getPosition();
}

bool UserPanel::isButtonModePressed()
{
  return pButtonMode->isPressed();
}

void UserPanel::sync()
{
  pButtonMode->sync();
}
