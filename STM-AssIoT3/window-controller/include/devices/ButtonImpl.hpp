#pragma once

#include "Button.hpp"

class ButtonImpl: public Button {
 
public: 
  ButtonImpl(int pin);
  bool isPressed();
  bool isClicked();

  void sync();

private:
  int pin;
  bool pressed;
  bool clicked;
};
