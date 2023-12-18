
#include "msp430g2553.h"

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  P1DIR |= (BIT0+BIT6);
  
  while(1){
    P1OUT ^= (BIT0+BIT6);
    __delay_cycles(1000000);
  }
}
