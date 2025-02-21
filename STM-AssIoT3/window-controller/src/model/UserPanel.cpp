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

void UserPanel::setSystemMode(const SystemMode mode)
{
  currentMode = mode;
}

SystemMode UserPanel::getSystemMode()
{
  return currentMode;
}

int UserPanel::getWindowOpeningPercentage()
{
  return pWindow->getPosition();
}

bool UserPanel::isButtonModePressed(){
  return pButtonMode->isPressed();
}

void UserPanel::sync()
{
  pButtonMode->sync();
  if (isButtonModePressed())
  {
    currentMode = currentMode == AUTOMATIC ? MANUAL : AUTOMATIC;
    Serial.println("MODE:CHANGE");
  }
}
