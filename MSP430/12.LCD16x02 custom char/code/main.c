
#include "msp430g2553.h"
#include "lcd.h"
#include "string.h"

unsigned char Add_sub[8] = {0x04, 0x04, 0x1F, 0x04, 0x04, 0x00, 0x1F, 0x00};
unsigned char Water[8] = {0x04, 0x0A, 0x0A, 0x11, 0x11, 0x11, 0x0E, 0x00};
unsigned char Temp[8] = {0x04, 0x0A, 0x0A, 0x0E, 0x1F, 0x1F, 0x0E, 0x00};
unsigned char Umbe[8] = {0x0E, 0x1F, 0x04, 0x04, 0x04, 0x04, 0x06, 0x00};
unsigned char Setup[8] = {0x11, 0x11, 0x11, 0x1F, 0x0E, 0x0A, 0x0E, 0x00};
unsigned char Water2[8] = {0x04, 0x0E, 0x0E, 0x1F, 0x1F, 0x1F, 0x0E, 0x00};
unsigned char Contro[8] = {0x00, 0x04, 0x06, 0x1F, 0x1F, 0x06, 0x04, 0x00};
unsigned char test[8] = {    0x00,
  0x00,
  0x0E,
  0x1F,
  0x1F,
  0x0E,
  0x00,
  0x00};

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  
  // Tat dao dong ngoai o chan P2.6 va P2.7 de su dung chan GPIO cho LCD
  P2SEL &=~ (BIT6 + BIT7); 
  
  InitializeLcm();
  
  LCD_Custom_Char(0, Add_sub);
  LCD_Custom_Char(1, Water);
  LCD_Custom_Char(2, Temp);
  LCD_Custom_Char(3, Umbe);
  LCD_Custom_Char(4, Setup);
  LCD_Custom_Char(5, Water2);
  LCD_Custom_Char(6, Contro);
  LCD_Custom_Char(7, test);
  
  ClearLcmScreen();
  
  while (1)
  {
    
    LcmSetCursorPosition(0, 0);
    PrintChar(0);
    LcmSetCursorPosition(0, 2);
    PrintChar(1);
    LcmSetCursorPosition(0, 4);
    PrintChar(2);
    LcmSetCursorPosition(0, 6);
    PrintChar(3);
    LcmSetCursorPosition(0, 8);
    PrintChar(4);
    LcmSetCursorPosition(0, 10);
    PrintChar(5);
    LcmSetCursorPosition(0, 12);
    PrintChar(6);
    LcmSetCursorPosition(0, 14);
    PrintChar(7);
  }
}
