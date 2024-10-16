#include <LiquidCrystal_I2C.h>
#include "lcd.h"

#define ADDR 0x27

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(ADDR, LCD_COLUMNS, LCD_LINES);
char empty[LCD_COLUMNS - INIT_LCD_COL];

void empty_line(unsigned char col, unsigned char row){
    lcd.setCursor(col, row);
    lcd.print(empty);
}

void initialize_lcd(void){
    lcd.init();
    int i = 0;
    for (i = 0; i < LCD_COLUMNS - INIT_LCD_COL - 1; i++){
        empty[i] = ' ';
    }
    empty[i] = '\0';
}

void lcd_wakeup(void){
    lcd.on();
    lcd.backlight();
    lcd.display();
}

void lcd_shutdown(void){
    lcd.flush();
    lcd.clear();
    lcd.noBacklight();
    lcd.noDisplay();
    lcd.off();
}

void print_first_line(const char * content){
    empty_line(INIT_LCD_COL, 0);
    lcd.setCursor(INIT_LCD_COL, 0);
    lcd.print(content);
}

void print_second_line(const char * content){
    empty_line(INIT_LCD_COL, 1);
    lcd.setCursor(INIT_LCD_COL, 1);
    lcd.print(content);
}

void print_third_line(const char * content){
    empty_line(INIT_LCD_COL, 2);
    lcd.setCursor(INIT_LCD_COL, 2);
    lcd.print(content);
}

void print_fourth_line(const char * content){
    empty_line(INIT_LCD_COL, 3);
    lcd.setCursor(INIT_LCD_COL, 3);
    lcd.print(content);
}
