
#define LCD_OUT P2OUT
#define LCD_DIR P2DIR

#define Clock BIT0
#define Data BIT1
#define Storage BIT2

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