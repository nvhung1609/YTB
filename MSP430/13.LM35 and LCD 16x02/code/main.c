
#include "msp430f2122.h"
#include "lcd.h"
#include "lm35.h"

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
  
  init_lm35();//khoi tao adc cho lm35
  
  while (1)
  {
    LcmSetCursorPosition(0, 0);//set vi tri lcd (hang,cot)
    PrintStr("NGUYEN VIET HUNG");//in chuoi ra mang hinh
    
    int nhiet_do = read_lm35();

    ftoa_1(arr,nhiet_do);//bien doi 1 so thuc sang chuoi de hien thi len LCD
    
    LcmSetCursorPosition(1, 0);//set vi tri lcd (hang,cot)
    PrintStr("NHIET DO: ");//in chuoi ra mang hinh
    PrintStr(arr);
  }
}
