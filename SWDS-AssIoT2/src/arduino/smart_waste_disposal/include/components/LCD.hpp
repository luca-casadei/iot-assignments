#pragma once
class hd44780_I2Cexp;

class LCD
{
public:
    LCD(unsigned int lcd_address, unsigned int lcd_columns, unsigned int lcd_rows);
    virtual ~LCD();
    void on();
    void off();
    void printToLine(unsigned int line_n, const char * text);
    void init();

private:
    hd44780_I2Cexp * lcd;
    char *empty_line;
};