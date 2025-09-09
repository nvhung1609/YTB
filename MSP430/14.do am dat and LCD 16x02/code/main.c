
#include "msp430f2122.h"
#include "lcd.h"
#include "sensor.h"

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
  
  init_sensor();
  
  while (1)
  {
    LcmSetCursorPosition(0, 0);//set vi tri lcd (hang,cot)
    PrintStr("NGUYEN VIET HUNG");//in chuoi ra mang hinh

    int do_am_dat = read_sensor();
    
    ftoa_1(arr,do_am_dat);//bien doi 1 so thuc sang chuoi de hien thi len LCD
    
    LcmSetCursorPosition(1, 0);//set vi tri lcd (hang,cot)
    PrintStr("DO AM DAT: ");//in chuoi ra mang hinh
    PrintStr(arr);
  }
}
