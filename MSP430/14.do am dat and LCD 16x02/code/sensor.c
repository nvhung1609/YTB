
#include "sensor.h"

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void init_sensor(void){
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + REFON + SREF_1; 
  __delay_cycles(30);
  ADC10CTL1 = INCH_0;
  __delay_cycles(30);
  ADC10AE0 |= BIT0;
}

int read_sensor(void){
  int do_am_dat;
  ADC10CTL0 &=~ ADC10IFG;          
  ADC10CTL0 |= ENC + ADC10SC;      
  while(!(ADC10CTL0 & ADC10IFG));  
  do_am_dat = map(ADC10MEM, 0, 1023, 0, 100);   
  ADC10CTL0 &=~ (ENC+ ADC10SC);   
  return do_am_dat;
}