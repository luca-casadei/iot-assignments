#include "./devices/TempSensorLM35.hpp"
#include "Arduino.h"

#define VCC ((float)5)

TempSensorLM35::TempSensorLM35(int p) : pin(p){
} 
  
float TempSensorLM35::getTemperature(){
  float values[5];
  float max = -1;
  float min = 100; 
  
  for (int i = 0; i < 5; i++){
    int value = analogRead(pin);
    float valueInCelsius = value / 10;
    values[i] = valueInCelsius;    
    if (valueInCelsius < min){
      min = valueInCelsius;
    } else if (valueInCelsius > max){
      max = valueInCelsius;
    }
  }
  float sum = 0;
  int count = 0;
  for (int i = 0; i < 5; i++){
    if ((values[i] > min) && (values[i] < max)){
      sum = sum + values[i];
      count++;
    }
  }
  if (count == 0){
    return values[0];
  } else {
    return sum/count;
  }
}
