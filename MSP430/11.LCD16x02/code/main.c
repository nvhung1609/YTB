
#include "msp430g2553.h"
#include "lcd.h"

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
    LcmSetCursorPosition(0, 0);//set vi tri lcd (hang,cot)
    PrintStr("NGUYEN VIET HUNG");//in chuoi ra mang hinh
    
    
    ftoa_1(arr,72);//bien doi 1 so thuc sang chuoi de hien thi len LCD
    
    LcmSetCursorPosition(1, 0);//set vi tri lcd (hang,cot)
    PrintStr("NHIET DO: ");//in chuoi ra mang hinh
    PrintStr(arr);
  }
}
