#include "./model/UserPanel.hpp"
#include <Arduino.h>
#include "pins.hpp"
#include "model/HWPlatform.hpp"

UserPanel::UserPanel(HWPlatform* pHW) {
    pLcd = pHW->getUserPanelLcd();
    pButtonMode = pHW->getModeButton();
}

void UserPanel::init(){
  pLcd->init();
  turnOnDisplay();
}

void UserPanel::turnOnDisplay(){
    pLcd->on();
}

void UserPanel::turnOffDisplay(){
    pLcd->off();
}

bool UserPanel::pressedOpen(){
  return modePressed;
}

void UserPanel::sync(){
  pButtonMode->sync();
  modePressed = pButtonMode->isPressed();
}



