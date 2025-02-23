#pragma once

#include "Button.hpp"

class ButtonImpl: public Button {
 
public:
  ButtonImpl(const int pin);
  bool isPressed();
  bool isClicked();

  void sync() override final;

private:
  int pin;
  bool pressed;
  bool clicked;
};
