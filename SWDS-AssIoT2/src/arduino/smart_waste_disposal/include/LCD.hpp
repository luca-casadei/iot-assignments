#include "ILCD.hpp"
#include <LiquidCrystal_I2C.h>

class LCD : public ILCD{
    public:
    LCD(unsigned int lcd_address, unsigned int lcd_columns, unsigned int lcd_rows);
    ~LCD();
    void on();
    void off();
    void printToLine(unsigned int, const char *);
    private:
    LiquidCrystal_I2C * lcd;
    char * empty_line;
};