
#include "msp430g2553.h"
#include "i2c_lcd.h"
#include "dht11.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  
  LCD_Init(0X27, 2, 16);//khoi tao LCD voi giao thuc i2c
  LCD_backlightOn();//cho phep bat den nen
  LCD_Clear();//clear mang hinh de xoa ky tu vo dinh
  
  while(1){
    readDHT11();//get du lieu dht11
    
    LCD_SetCursor(0,0);//set vi tri lcd(cot, hang)
    LCD_Print("NHIET DO: ");//in chuoi ra mang hinh
    lcd_put_num(nhietDo,0,0);//chuyen so thuc sang chuoi va in ra mang hinh
    
    LCD_SetCursor(0,1);//set vi tri lcd(cot, hang)
    LCD_Print("DO AM: ");//in chuoi ra mang hinh
    lcd_put_num(doAm,0,0);//chuyen so thuc sang chuoi va in ra mang hinh
  }
}