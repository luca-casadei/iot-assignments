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

SystemState UserPanel::selectedMode()
{
  return actualMode;
}

int UserPanel::getWindowOpeningPercentage() 
{
  return pWindow->getPosition();
}

void UserPanel::sync()
{
  pButtonMode->sync();
  if (pButtonMode->isPressed())
  {
    actualMode = actualMode==AUTOMATIC ? MANUAL : AUTOMATIC;
  }
}
