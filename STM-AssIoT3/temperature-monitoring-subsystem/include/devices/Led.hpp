#pragma once

#include "./Light.hpp"

class Led: public Light { 
public:
  Led(int pin);
  void switchOn();
  void switchOff();    
protected:
  int pin;  
};