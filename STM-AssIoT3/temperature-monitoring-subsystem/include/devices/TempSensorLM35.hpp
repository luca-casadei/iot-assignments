#pragma once

#include "./TempSensor.hpp"

class TempSensorLM35: public TempSensor {
public:
  TempSensorLM35(int p);
  virtual float getTemperature();
private:
  int pin;
};
