
#include "lm35.h"

void init_lm35(void){
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + REFON + SREF_1; 
  __delay_cycles(30);
  ADC10CTL1 = INCH_0;
  __delay_cycles(30);
  ADC10AE0 |= BIT0;
}

int read_lm35(void){
  int nhiet_do;
  ADC10CTL0 &=~ ADC10IFG;          
  ADC10CTL0 |= ENC + ADC10SC;      
  while(!(ADC10CTL0 & ADC10IFG));  
  nhiet_do = (int)((float)(ADC10MEM*1.5*100)/1024);   
  ADC10CTL0 &=~ (ENC+ ADC10SC);   
  return nhiet_do;
}