
#include "msp430g2553.h"

#define CLOCK BIT0
#define DATA BIT1
#define LATCH BIT2

#define OUT595 P1OUT

void clock(int x);
void data(int x);
void latch(void);

void main( void )
{
  WDTCTL = WDTPW + WDTHOLD;
  
  P1DIR |= (CLOCK + DATA + LATCH);//khai bao ngo ra
  
  while(1){
    data(1);
    clock(1);
    
    data(0);
    clock(6);
    
    data(1);
    clock(1);
    
    latch();
    
    __delay_cycles(100000);
  }
}

void clock(int x){
  for(int i=0; i<x; i++){
    OUT595 |= CLOCK;//ngo ra muc cao
    OUT595 &=~ CLOCK;//ngo ra muc thap
  }
}

void data(int x){
  if(x){
    OUT595 |= DATA;//ngo ra muc cao
  }
  else{OUT595 &=~ DATA;}//ngo ra muc thap
}

void latch(void){
  OUT595 |= LATCH;//ngo ra muc cao
  OUT595 &=~ LATCH;//ngo ra muc thap
}