#include <Arduino.h>
#include "classes/ComponentTester.hpp"
#include "pins.hpp"

#define TEST_COMPONENTS

#ifdef TEST_COMPONENTS
ICompoentTest * tester;
#endif

void setup()
{
    Serial.begin(9600);
#ifdef TEST_COMPONENTS
    tester = new ComponentTester(GREEN_PIN, RED_PIN, SERVO_PIN);
    tester->init();
#endif
    //Task initialization
    // TODO
}

void loop()
{
#ifdef TEST_COMPONENTS
    tester->test();
#else
    // TASKS
    // TODO
#endif
}