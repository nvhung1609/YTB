
#include "msp430g2553.h"
#include "lcd.h"
#include "dht11.h"

char arr[10];

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  
  //Tat dao dong ngoai o chan P2.6 va P2.7 de su dung chan GPIO cho LCD
  P2SEL &=~ (BIT6 + BIT7); 
  
  InitializeLcm();//khoi tao lcd
  ClearLcmScreen();//claer mang hinh lcd
  
  while (1)
  {
    readDHT11();//get du lieu dht11
    
    int nhiet_do = nhietDo;
    int do_am = doAm;
    
    ftoa_1(arr,nhiet_do);//bien doi 1 so thuc sang chuoi de hien thi len LCD
    LcmSetCursorPosition(0, 0);//set vi tri lcd (hang,cot)
    PrintStr("NHIET DO: ");//in chuoi ra mang hinh
    PrintStr(arr);
    
    ftoa_1(arr,do_am);//bien doi 1 so thuc sang chuoi de hien thi len LCD
    LcmSetCursorPosition(1, 0);//set vi tri lcd (hang,cot)
    PrintStr("DO AM: ");//in chuoi ra mang hinh
    PrintStr(arr);
  }
}
