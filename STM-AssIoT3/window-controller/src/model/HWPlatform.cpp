#include "HWPlatform.hpp"
#include <Arduino.h>
#include "devices/ButtonImpl.hpp"
#include "kernel/MsgService.hpp"
#include "pins.hpp"
#include "devices/servo_motor_impl.hpp"

void wakeUp(){}

HWPlatform::HWPlatform(){
  pLcd = new LiquidCrystal_I2C(0x27,20,4);
  pButtonMode = new ButtonImpl(BUTTON_MODE_PIN);
  pMotorWindow = new ServoMotorImpl(MOTOR_PIN);
}


void HWPlatform::init(){
  pLcd->init();
  pLcd->backlight();
}

  Button* HWPlatform::getModeButton(){
    return this->pButtonMode;
  }

  LiquidCrystal_I2C* HWPlatform::getUserPanelLcd(){
    return this->pLcd;
  }

  ServoMotor* HWPlatform::getWindowMotor(){
    return this->pMotorWindow;
  }

