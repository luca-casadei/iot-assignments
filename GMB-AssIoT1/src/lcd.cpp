#include <LiquidCrystal_I2C.h>
#include "lcd.h"

#define LINES 4
#define ADDR 0x27
#define INIT_COL 2

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(ADDR, COLUMNS,LINES);
char empty[COLUMNS - INIT_COL];

static void empty_line(unsigned char col, unsigned char row){
    lcd.setCursor(col, row);
    lcd.print(empty);
}

void initialize_lcd(void){
    lcd.init();
    int i = 0;
    for (i = 0; i < COLUMNS - INIT_COL - 1; i++){
        empty[i] = ' ';
    }
    empty[i] = '\0';
}

void print_second_line(const char * content){
    empty_line(INIT_COL, 1);
    lcd.setCursor(INIT_COL, 1);
    lcd.print(content);
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

void print_third_line(const char * content){
    empty_line(INIT_COL, 2);
    lcd.setCursor(INIT_COL, 2);
    lcd.print(content);
}

void print_fourth_line(const char * content){
    empty_line(INIT_COL, 3);
    lcd.setCursor(INIT_COL, 3);
    lcd.print(content);
}

void print_first_line(const char * content){
    empty_line(INIT_COL, 0);
    lcd.setCursor(INIT_COL, 0);
    lcd.print(content);
}