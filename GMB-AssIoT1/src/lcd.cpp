#include <LiquidCrystal_I2C.h>
#include "lcd.h"

#define LINES 4
#define ADDR 0x27
#define INIT_COL 2

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(ADDR, COLUMNS,LINES);
char empty[COLUMNS - INIT_COL];

void initialize_lcd(void){
    lcd.init();
    lcd.backlight();
    int i = 0;
    for (i = 0; i < COLUMNS - INIT_COL - 1; i++){
        empty[i] = ' ';
    }
    empty[i] = '\0';
}

void print_second_line(const char * content){
    lcd.setCursor(INIT_COL, 1);
    lcd.print(empty);
    lcd.setCursor(INIT_COL, 1);
    lcd.print(content);
}

void lcd_shutdown(){
    lcd.flush();
    lcd.clear();
    lcd.off();
}

void print_third_line(const char * content){
    lcd.setCursor(INIT_COL, 2);
    lcd.print(empty);
    lcd.setCursor(INIT_COL, 2);
    lcd.print(content);
}