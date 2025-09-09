#ifndef	DELAY_H_
#define	DELAY_H_

#include <stdint.h>
#include <msp430.h>

#define F_CPU   8

void delay_us(uint16_t value);
void delay_ms(uint16_t value);

#endif /* DELAY_H_ */