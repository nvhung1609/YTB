
#include "MSP430G2553.h"

void main( void )
{
  WDTCTL = WDTPW + WDTHOLD;
  
//  BCSCTL1 = CALBC1_16MHZ;
//  DCOCTL  = CALDCO_16MHZ;
  
  DCOCTL  = 0x9b;
  BCSCTL1 = 0x8f;
  BCSCTL2 = 0x00;
  BCSCTL3 = 0x04;
  
  P1DIR |= BIT4;
  
  while(1)
  {
    P1OUT ^= BIT4;
    __delay_cycles(1000000);
  }
}

//IAR: C:\Users\PC\Desktop\MSP430KIT\BSLDEMO-2.01\BSLDEMO-2.01c.exe -cCOM3 -m1 -ijevpr C:\Users\PC\Desktop\MSP430KIT\IAR\Debug\Exe\test.txt
//CCS: C:\Users\PC\Desktop\MSP430KIT\BSLDEMO-2.01\BSLDEMO-2.01c.exe -cCOM3 -m1 -ijevpr ${BuildArtifactFileBaseName}.txt