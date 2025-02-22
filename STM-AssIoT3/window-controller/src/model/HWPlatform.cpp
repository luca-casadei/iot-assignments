#include "./model/HWPlatform.hpp"
#include <Arduino.h>
#include "devices/ButtonImpl.hpp"
#include "kernel/MsgService.hpp"
#include "constants.hpp"
#include "devices/servo_motor_impl.hpp"

HWPlatform::HWPlatform()
{
  pLcd = new LCD(LCD_ADDR, LCD_COLS, LCD_ROWS);
  pButtonMode = new ButtonImpl(BUTTON_MODE_PIN);
  pMotorWindow = new ServoMotorImpl(MOTOR_PIN);
}

void HWPlatform::init()
{
  pLcd->init();
}

Button *HWPlatform::getModeButton()
{
  return this->pButtonMode;
}

LCD *HWPlatform::getUserPanelLcd()
{
  return this->pLcd;
}

ServoMotor *HWPlatform::getWindowMotor()
{
  return this->pMotorWindow;
}
