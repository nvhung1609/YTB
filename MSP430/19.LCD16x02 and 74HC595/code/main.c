
#include "msp430g2553.h"
#include "lcd595.h"

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
    
    lcd_goto(2,1);
    lcd_puts("LCD-74HC595");
    
    __delay_cycles(1000000);    
    lcd_temizle();
    
    lcd_goto(1,1);
    lcd_puts("MSP430G2553");
    
    lcd_goto(2,1);
    lcd_puts("LCD16x02-74HC595");
    
    __delay_cycles(1000000);    
    lcd_temizle();
  }
}