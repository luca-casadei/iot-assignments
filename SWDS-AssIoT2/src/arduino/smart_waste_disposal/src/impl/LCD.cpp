#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "classes/LCD.hpp"

LCD::LCD(unsigned int lcd_address, unsigned int lcd_columns, unsigned int lcd_rows)
{
    this->lcd = new hd44780_I2Cexp(lcd_address, lcd_columns, lcd_rows);
    this->empty_line = (char *)malloc(sizeof(char) * lcd_columns);
    unsigned int i = 0;
    for (i = 0; i < lcd_columns - 1; i++)
    {
        this->empty_line[i] = ' ';
    }
    this->empty_line[i] = '\0';
}

void LCD::init(){
    lcd->init();
}

LCD::~LCD()
{
    free(this->empty_line);
}

void LCD::on()
{
    lcd->clear();
    lcd->backlight();
}

void LCD::off()
{
    lcd->clear();
    lcd->noBacklight();
}

void LCD::printToLine(const unsigned int line_n, const char *text)
{
    lcd->setCursor(0, line_n);
    lcd->print(this->empty_line);
    lcd->setCursor(0, line_n);
    lcd->print(text);
}