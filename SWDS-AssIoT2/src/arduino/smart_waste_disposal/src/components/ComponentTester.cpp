#include "components/ComponentTester.hpp"
#include "components/LCD.hpp"
#include "components/Led.hpp"
#include "components/ServoMotor.hpp"
#include <Arduino.h>

ComponentTester::ComponentTester(const unsigned int green_led_pin, const unsigned int red_led_pin, const unsigned int servo_pin){
    this->lcd = new LCD(0x27,20,4);
    this->led_green = new Led(green_led_pin);
    this->led_red = new Led(red_led_pin);
    this->sv = new ServoMotor(servo_pin);
};

ComponentTester::~ComponentTester(){
    delete this->lcd;
    delete this->led_green;
    delete this->led_red;
    delete this->sv;
};

void ComponentTester::init(){
    this->lcd->init();
    this->sv->init();
    this->led_green->init();
    this->led_red->init();
}

void ComponentTester::test(){
    delay(2000);
    this->led_green->switchOn();
    this->led_red->switchOff();
    this->lcd->on();
    this->lcd->printToLine(2, "Ehi");
    this->sv->open();
    delay(2000);
    this->lcd->printToLine(2, "Ciao!");
    this->sv->empty();
    delay(2000);
    this->sv->close();
    this->lcd->off();
    this->led_red->switchOn();
    this->led_green->switchOff();
}