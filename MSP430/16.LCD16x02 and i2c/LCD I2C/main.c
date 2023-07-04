
#include "msp430g2553.h"
#include "i2c_lcd.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  
  LCD_Init(0X27, 2, 16);//khoi tao LCD voi giao thuc i2c
  LCD_backlightOn();//cho phep bat den nen
  LCD_Clear();//clear mang hinh de xoa ky tu vo dinh
  
  while(1){
    LCD_SetCursor(0,0);//set vi tri lcd (cot, hang)
    LCD_Print("NGUYEN VIET HUNG");//in chuoi ra mang hinh
    
    LCD_SetCursor(0,1);//set vi tri lcd (cot, hang)
    lcd_put_num(1234,0,0);//chuyen so thuc sang chuoi va in ra mang hinh
  }
}