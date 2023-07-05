#include "i2c_lcd.h"

uint8_t _rows;
uint8_t _cols;
uint8_t displayFunction;
uint8_t displayControl;
uint8_t displayMode;
uint8_t backlightVal;

int LCD_Init(uint8_t lcd_address, uint8_t lcd_rows, uint8_t lcd_cols)
{
    _rows = lcd_rows;
    _cols = lcd_cols;

    I2C_USCI_Init(lcd_address);

    // Default display, text direction, and back light
    displayFunction = LCD_4_BITMODE | LCD_1_LINE | LCD_5x8_DOTS;

    if(_rows > 1)
    {
        displayFunction = LCD_4_BITMODE | LCD_2_LINE | LCD_5x8_DOTS;
    }

    // Initialize to default text direction (for roman languages)
    displayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

    backlightVal = LCD_BACKLIGHT;

    // We need at least 40ms after power rises above 2.7V
    delay_us(40 * 100);

    // Now we pull both RS and R/W low to begin commands
    expanderWrite(backlightVal);

    // We start in 8 bit mode, try to set 4 bit mode
    write4bits(0x03 << 4);
    delay_us(45 * 100); // Wait more than 4.1ms

    // Second try
    write4bits(0x03 << 4);
    delay_us(45 * 100); // Wait more than 4.1ms

    // Third try
    write4bits(0x03 << 4);
    delay_us(150); // Wait more than 100us

    // Finally, set to 4-bit interface
    write4bits(0x02 << 4);

    // Set number of lines, font size...
    command(LCD_FUNCTIONSET | displayFunction);

    // Turn the display on with blinking cursor for default
    displayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    LCD_displayOn();

    // Clear it off
    LCD_Clear();

    // Set the entry mode
    command(LCD_ENTRYMODESET | displayMode);

    // Set cursor to start position
    LCD_Home();

    return 1;
}

/********************************
 * Clear display and set cursor position to zero
 * This command takes a long time (delay needed)
 ********************************/
void LCD_Clear(void)
{
    command(LCD_CLEARDISPLAY);
    delay_us(45 * 100);
}

/********************************
 * Set cursor position to zero
 * This command takes a long time (delay needed)
 ********************************/
void LCD_Home(void)
{
    command(LCD_RETURNHOME);
    delay_us(45 * 100);
}

/********************************
 * Turn the display on or off
 * This isn't the same as turning on/off the backlight
 ********************************/
void LCD_displayOn(void)
{
    displayControl |= LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | displayControl);
}

void LCD_displayOff(void)
{
    displayControl &= ~LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | displayControl);
}

/********************************
 * Set the location of the cursor assuming 16x2 LCD
 * Numbering is based on zero indexed arrays
 * For example, rows are 0 or 1 (top or bottom)
 ********************************/
void LCD_SetCursor(uint8_t cols, uint8_t rows)
{
    // Sanity check row and columns...
    // No need to check less than 0 on unsigned byte
    int row_offsets[] = {0x00, 0x40, 0x14, 0x54};

    if(rows > _rows)
    {
       rows = _rows - 1; // We count rows starting w/0
    }

    command(LCD_SETDDRAMADDR | (cols + row_offsets[rows]));
}

/********************************
 * Display or hide the cursor
 ********************************/
void LCD_cursorOn(void)
{
    displayControl |= LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | displayControl);
}

void LCD_cursorOff(void)
{
    displayControl &= ~LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | displayControl);
}

/********************************
 * Turn blinking cursor on/off
 ********************************/
void LCD_blinkOn(void)
{
    displayControl |= LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | displayControl);
}

void LCD_blinkOff(void)
{
    displayControl &= ~LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | displayControl);
}

/********************************
 * Shifts the text on display 1 position to right or left
 * These functions will wrap text (they'll come out other side)
 ********************************/
void LCD_shiftDisplayLeft(void)
{
    command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCD_shiftDisplayRight(void)
{
    command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

/********************************
 * Set the direction or writing text to
 * left -> right or right -> left
 * Default is left to right
 ********************************/
void LCD_textLeftToRight(void)
{
    displayMode |= LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | displayMode);
}

void LCD_textRightToLeft(void)
{
    displayMode &= ~LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | displayMode);
}

/********************************
 * This will right justify text if on
 * Or left justify if off
 ********************************/
void LCD_autoscrollOn(void)
{
    displayMode |= LCD_ENTRYSHIFTINCREMENT;
    command(LCD_ENTRYMODESET | displayMode);
}

void LCD_autoscrollOff(void)
{
    displayMode &= ~LCD_ENTRYSHIFTINCREMENT;
    command(LCD_ENTRYMODESET | displayMode);
}

/********************************
 * Turn the back light on or off
 * Default is on
 ********************************/
void LCD_backlightOn(void)
{
    backlightVal = LCD_BACKLIGHT;
    expanderWrite(0);
}

void LCD_backlightOff(void)
{
    backlightVal = LCD_NOBACKLIGHT;
    expanderWrite(0);
}

/********************************
 * Returns 1 if back light is on, 0 if off
 ********************************/
int LCD_isBacklightOn(void)
{
    if(backlightVal == LCD_BACKLIGHT)
    {
        return 1;
    }

    return 0;
}

/********************************
 * We can create and store up to 8 custom characters to CGRAM
 * Look at data sheet starting at page 13
 *
 * memAddress: Location in EEPROM (0 - 7)
 * charMap: Array of uint8 that represent custom character
 * Only the 5 least significant bits are looked at
 *
 * Example using a heart :
 * uint8_t heart[CHAR_HEIGHT] = { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00 };
 * [ 0 0 0 0 0      -> 0x00 = 0b00000
 *   0 1 0 1 0      -> 0x0A = 0b01010
 *   1 1 1 1 1      -> 0x1F = 0b11111
 *   1 1 1 1 1      -> 0x1F = 0b11111
 *   0 1 1 1 0      -> 0x0E = 0b01110
 *   0 0 1 0 0      -> 0x04 = 0b00100
 *   0 0 0 0 0 ]    -> 0x00 = 0b00000
 *   0 0 0 0 0 (Cursor)
 *
 *   Last row of bits (8th row) is dedicated to cursor
 *   Custom char generator: https://omerk.github.io/lcdchargen/
 ********************************/
void LCD_createChar(uint8_t location, uint8_t charMap[])
{
    // Sanity check that address is between 0 - 7
    location &= 0x7; // We only have 8 locations 0 - 7

    // Send mask of CGRAM address and location shifted 3 bits (page 19)
    command(LCD_SETCGRAMADDR | (location << 3));

    // Write each line of bits
    uint32_t i;

    for(i = 0; i < 8; i++)
    {
        LCD_writeChar(charMap[i]);
    }
}

void LCD_load_custom_character(uint8_t char_num, uint8_t *rows)
{
    LCD_createChar(char_num, rows);
}

/********************************
 * Writes a single character to the LCD
 * Wraps the cursor if position isn't on screen
 ********************************/
void LCD_writeChar(uint8_t data)
{
    send(data, REG_SELECT_BIT);
}

/********************************
 * Writes a string to the LCD
 ********************************/
void LCD_Print(char word[])
{
    uint8_t i = 0;
    uint8_t size = strlen(word);

    for(i = 0; i < size; i++)
    {
        LCD_writeChar(word[i]);
    }
}

/********************************
 * Handles the processing of display commands
 * Not related to writing characters to screen
 * We'll make this internal for abstraction
 ********************************/
void command(uint8_t data)
{
    send(data, 0);
}

/********************************
 * Processing for sending data for 4 bit mode
 ********************************/
void send(uint8_t data, uint8_t mode)
{
    uint8_t highnib = data & 0xf0;
    uint8_t lownib = (data << 4) & 0xf0;

    write4bits(highnib | mode);
    write4bits(lownib | mode);
}

/********************************/
void write4bits(uint8_t data)
{
    expanderWrite(data);
    pulseEnable(data);
}

/********************************/
void pulseEnable(uint8_t data)
{
    expanderWrite(data | ENABLE_BIT); // Enable bit high
    delay_us(1); // Enable pulse must be > 450ns

    expanderWrite(data & ~ENABLE_BIT); // Enable bit low
    delay_us(50); // Command needs > 37us to settle
}

/********************************
 * Write single byte to I2C data line
 ********************************/
void expanderWrite(uint8_t data)
{
    I2C_USCI_Write_Byte(LCD_Address >> 1, data | backlightVal);
}
void lcd_put_num(unsigned long val, char dec, unsigned char neg)
{
  char i, j, k, digit;
  long total, temp;
  for(i=0, total=val; total>0; i++)     // count number
  total /= 10;
  total = i;
  if(neg != 0)
  LCD_writeChar('-');
  if((total-dec) <= 0)  // if total < dec put 0.xxx
  LCD_writeChar('0');
  else
  {      
    for(i=0; i<(total-dec); i++)
    {
      temp = 1;
      for(j=1; j<(total-i); j++)
        temp *= 10;
      digit = (val / temp) % 10;
      LCD_writeChar(digit + 0x30);
    }
  }
  if(dec > 0)
  {
    LCD_writeChar('.');
    if((dec-total) > 0) // exp: val = 55; dec = 3 put 0.055
    {
      for(i=0; i<(dec-total); i++)
        LCD_writeChar('0');
      k = 0;
    }
    else
      k = total - dec;
    for(i=k; i<total; i++)
    {
      temp = 1;
      for(j=1; j<(total-i); j++)
        temp *= 10;
      digit = (val / temp) % 10;
      LCD_writeChar(digit + 0x30);
    }
  }    
}