#include <msp430g2553.h>

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer

	  DCOCTL  = 0x9b;
	  BCSCTL1 = 0x8f;
	  BCSCTL2 = 0x00;
	  BCSCTL3 = 0x04;
	  //giao dong 16MHz
	P1DIR |= BIT0 + BIT6;

	while(1)
	{
	    P1OUT ^= BIT0 + BIT6;
	    __delay_cycles(1000000);//1s
	}
}
