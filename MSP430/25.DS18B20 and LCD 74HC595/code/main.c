
#include "msp430g2553.h"
#include "lcd595.h"
#include "ds18b20.h"

char arr[10];

void main(void)
{
  WDTCTL =  WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL =  CALDCO_1MHZ;
  
  lcd_init();
  
  while(1)
  {
    lcd_goto(1,1);
    lcd_puts("NGUYEN VIET HUNG");
    
    int data_ds18=(int)DS18B20();
    convert(arr,data_ds18);
    
    lcd_goto(2,1);
    lcd_puts("NHIET DO: ");
    lcd_puts(arr);
  }
}