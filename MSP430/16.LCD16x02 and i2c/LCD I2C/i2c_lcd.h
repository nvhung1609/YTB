#ifndef	I2C_LCD_H_
#define	I2C_LCD_H_

#include <stdint.h>
#include <string.h>
#include "delay.h"
#include "i2c.h"

// Display commands
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80

// Text direction
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// Display controls
#define LCD_DISPLAYON           0x04
#define LCD_DISPLAYOFF          0x00
#define LCD_CURSORON            0x02
#define LCD_CURSOROFF           0x00
#define LCD_BLINKON             0x01
#define LCD_BLINKOFF            0x00

// Cursor shifts
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00

// Function controls
#define LCD_8_BITMODE           0x10
#define LCD_4_BITMODE           0x00
#define LCD_2_LINE              0x08
#define LCD_1_LINE              0x00
#define LCD_5x10_DOTS           0x04
#define LCD_5x8_DOTS            0x00

// Back light control
#define LCD_BACKLIGHT           0x08
#define LCD_NOBACKLIGHT         0x00

// Writing bits
#define REG_SELECT_BIT          0x01
#define READ_WRITE_BIT          0x02
#define ENABLE_BIT              0x04

#define LCD_Address             0x27

int LCD_Init(uint8_t lcd_addr, uint8_t lcd_rows, uint8_t lcd_cols);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_displayOn(void);
void LCD_displayOff(void);
void LCD_SetCursor(uint8_t cols, uint8_t rows);
void LCD_cursorOn(void);
void LCD_cursorOff(void);
void LCD_blinkOn(void);
void LCD_blinkOff(void);
void LCD_shiftDisplayLeft(void);
void LCD_shiftDisplayRight(void);
void LCD_textLeftToRight(void);
void LCD_textRightToLeft(void);
void LCD_autoscrollOn(void);
void LCD_autoscrollOff(void);
void LCD_backlightOn(void);
void LCD_backlightOff(void);
int LCD_isBacklightOn(void);
void LCD_createChar(uint8_t location, uint8_t charMap[]);
void LCD_load_custom_character(uint8_t char_num, uint8_t *rows);
void LCD_writeChar(uint8_t data);
void LCD_Print(char word[]);
void lcd_put_num(unsigned long val, char dec, unsigned char neg);
/********************************
 * File specific functions
 ********************************/
void command(uint8_t data);
void send(uint8_t data, uint8_t mode);
void write4bits(uint8_t data);
void pulseEnable(uint8_t data);
void expanderWrite(uint8_t data);

#endif /* I2C_LCD_H_ */
