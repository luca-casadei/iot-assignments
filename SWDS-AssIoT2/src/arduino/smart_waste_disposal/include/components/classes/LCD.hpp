#pragma once
#include "components/interfaces/ILCD.hpp"

class hd44780_I2Cexp;

class LCD : public ILCD
{
public:
    LCD(unsigned int lcd_address, unsigned int lcd_columns, unsigned int lcd_rows);
    ~LCD();
    void on() final;
    void off() final;
    void printToLine(unsigned int line_n, const char * text) final;
    void init() final;

private:
    hd44780_I2Cexp * lcd;
    char *empty_line;
};