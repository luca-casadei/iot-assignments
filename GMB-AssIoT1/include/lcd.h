/*
 * LCD columns and lines.
 */
#define LCD_COLUMNS 20
#define LCD_LINES 4

/*
 * It initializes the LCD.
 */
void initialize_lcd(void);

/*
 * It prints the content on the first line of the LCD.
 */
void print_first_line(const char * content);

/*
 * It prints the content on the second line of the LCD.
 */
void print_second_line(const char * content);

/*
 * It prints the content on the third line of the LCD.
 */
void print_third_line(const char * content);

/*
 * It prints the content on the fourth line of the LCD.
 */
void print_fourth_line(const char * content);

/*
 * It shutdowns the LCD.
 */
void lcd_shutdown(void);

/*
 * It wakes up the LCD.
 */
void lcd_wakeup(void);

/*
 * It empties a specific line of the LCD.
 */
void empty_line(unsigned char row);