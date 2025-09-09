
#include "msp430g2553.h"
#include "lcd595.h"
#include "dht11.h"

char arr[10];

void main(void)
{
  WDTCTL =  WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL =  CALDCO_1MHZ;
  
  lcd_init();
  
  while(1)
  {
    readDHT11();
    
    int nhiet_do = nhietDo;
    int do_am = doAm;
    
    convert(arr,nhiet_do);
    lcd_goto(1,1);
    lcd_puts("NHIET DO: ");
    lcd_puts(arr);
    
    convert(arr,do_am);
    lcd_goto(2,1);
    lcd_puts("DO AM: ");
    lcd_puts(arr);
  }
}