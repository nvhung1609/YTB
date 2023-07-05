
#define LCD_OUT P1OUT
#define LCD_DIR P1DIR

#define Clock BIT5
#define Data BIT6
#define Storage BIT7

#define nop() asm("nop")
 
void delay(unsigned long int);
void hc595_yaz(unsigned char);
void lcd_write(unsigned char);
void lcd_putch(unsigned char);
void lcd_puts(const char*);
void lcd_temizle(void);
void lcd_goto(char,char);
void lcd_init(void);
void convert(char* string, unsigned int a);