#include <Arduino.h>
#include "ServoMotor.hpp"
#include "LCD.hpp"

LCD lcd(0x27, 20, 4);
ServoMotor servo(10);
bool once = false;

void setup()
{
}

void loop()
{
    if (!once)
    {
        lcd.on();
        lcd.printToLine(1, "Ciao");
        once = true;
    }
}