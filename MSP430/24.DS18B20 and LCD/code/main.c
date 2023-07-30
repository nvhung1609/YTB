
#include "msp430g2553.h"
#include "lcd.h"
#include "ds18b20.h"

char arr[10];

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  
  P2SEL &=~ (BIT6 + BIT7); 
  
  InitializeLcm();
  ClearLcmScreen();
  
  while (1)
  {
    LcmSetCursorPosition(0, 0);
    PrintStr("NGUYEN VIET HUNG");
    
    int data_ds18 =(int)DS18B20();
    
    ftoa_1(arr,data_ds18);
    
    LcmSetCursorPosition(1, 0);
    PrintStr("NHIET DO: ");
    PrintStr(arr);
  }
}
