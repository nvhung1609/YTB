#include "delay.h"

void delay_us(uint16_t value)
{
    register uint16_t loops = ((F_CPU * value) >> 2);
    
    while(loops)
    {
        __delay_cycles(1);
        loops--;
    }
}
void delay_ms(uint16_t value)
{
    while(value)
    {
        delay_us(1000);
        value--;
    }
}