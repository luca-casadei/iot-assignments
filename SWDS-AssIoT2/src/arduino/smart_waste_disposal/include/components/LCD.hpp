#pragma once
class hd44780_I2Cexp;

class LCD
{
public:
    LCD(unsigned int lcd_address, unsigned int lcd_columns, unsigned int lcd_rows);
    virtual ~LCD();
    virtual void on() final;
    virtual void off() final;
    virtual void printToLine(unsigned int line_n, const char * text) final;
    virtual void init() final;

private:
    hd44780_I2Cexp * lcd;
    char *empty_line;
};