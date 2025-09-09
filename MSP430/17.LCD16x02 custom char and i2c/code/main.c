
#include "msp430g2553.h"
#include "i2c_lcd.h"

unsigned char customChar[8] = { 
  0x00,
  0x00,
  0x00,
  0x1F,
  0x00,
  0x1F,
  0x00,
  0x00
};

void main( void )
{
  WDTCTL = WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;      
  DCOCTL = CALDCO_1MHZ;
  
  LCD_Init(0X27, 2, 16);
  LCD_Clear(); //xoa cac ky tu vo dinh
  
  LCD_createChar(0, customChar);
  
  while(1)
  {
    LCD_SetCursor(0,0);//set vi tri lcd(cot, hang)
    LCD_Print("NGUYEN VIET HUNG");
    
    LCD_SetCursor(0,1);//set vi tri lcd(cot, hang)
    LCD_writeChar(0);//in char custom ra mang hinh
  }
}