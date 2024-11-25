#include "components/Component.hpp"

Component::Component(unsigned int pin){
    this->pin = pin;
}

unsigned int Component::getPin(){
    return this->pin;
}