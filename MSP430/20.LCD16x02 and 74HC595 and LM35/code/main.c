
#include "msp430f2122.h"
#include "lcd595.h"
#include "lm35.h"

char arr[10];

void main(void)
{
  WDTCTL =  WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL =  CALDCO_1MHZ;
  
  lcd_init();
  
  init_lm35();
  
  while(1)
  {
    lcd_goto(1,1);
    lcd_puts("NGUYEN VIET HUNG");
    
    int nhiet_do = read_lm35();
    
    convert(arr,nhiet_do);
    lcd_goto(2,1);
    lcd_puts("NHIET DO: ");
    lcd_puts(arr);
  }
}