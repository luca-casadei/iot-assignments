#include "UserPanel.hpp"
#include <Arduino.h>
#include "pins.hpp"
#include "model/HWPlatform.hpp"

UserPanel::UserPanel(HWPlatform* pHW) {
    pLcd = pHW->getUserPanelLcd();
    pButtonMode = pHW->getModeButton();
}

void UserPanel::init(){
  pLcd->init();
  pLcd->backlight();
  pLcd->noDisplay();
  turnOnDisplay();
}

void UserPanel::turnOnDisplay(){
  pLcd->display();
  pLcd->clear();
}

void UserPanel::turnOffDisplay(){
  pLcd->noDisplay();
}

bool UserPanel::pressedOpen(){
  return modePressed;
}

void UserPanel::sync(){
  pButtonMode->sync();
  modePressed = pButtonMode->isPressed();
}



