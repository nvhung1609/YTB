
#include "msp430f2122.h"
#include "lcd595.h"
#include "sensor.h"

char arr[10];

void main(void)
{
  WDTCTL =  WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL =  CALDCO_1MHZ;
  
  lcd_init();
  
  init_sensor();
  
  while(1)
  {
    lcd_goto(1,1);
    lcd_puts("NGUYEN VIET HUNG");
    
    int do_am_dat = read_sensor();
    
    convert(arr,do_am_dat);
    lcd_goto(2,1);
    lcd_puts("DO AM DAT: ");
    lcd_puts(arr);
  }
}