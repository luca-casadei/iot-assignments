#include <Arduino.h>
#include "classes/ServoMotor.hpp"
#include "classes/LCD.hpp"
#include "classes/Led.hpp"
#include "pins.hpp"

LCD lcd(LCD_ADDR, 20, 4);
ServoMotor sv(SERVO_PIN);
Led green_led(GREEN_PIN);
Led red_led(RED_PIN);

#define TEST_COMPONENTS
#ifdef TEST_COMPONENTS
void test_components(void)
{
    delay(2000);
    green_led.switchOn();
    red_led.switchOff();
    lcd.on();
    lcd.printToLine(2, "Ehi");
    sv.open();
    delay(2000);
    lcd.printToLine(2, "Ciao!");
    sv.empty();
    delay(2000);
    sv.close();
    lcd.off();
    red_led.switchOn();
    green_led.switchOff();
}
#endif

void setup()
{
    Serial.begin(9600);
#ifdef TEST_COMPONENTS
    /*
     * Component initialization
     */
    lcd.init();
    sv.init();
    green_led.init();
    red_led.init();
#endif
    //Task initialization
    // TODO
}

void loop()
{
#ifdef TEST_COMPONENTS
    test_components();
#else
    // TASKS
    // TODO
#endif
}