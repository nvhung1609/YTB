#include "i2c.h"

void I2C_USCI_Init(uint8_t slaveAddress)
{
    P1SEL |= BIT6 | BIT7;
    P1SEL2 |= BIT6 | BIT7;
    
    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 = UCMST | UCMODE_3 | UCSYNC;
    UCB0CTL1 = UCSSEL_2 | UCSWRST;
    UCB0BR0 = 12;
    UCB0BR1 = 0;
    UCB0I2CSA = slaveAddress;
    UCB0CTL1 &= ~UCSWRST;
}

void I2C_USCI_Set_Address(uint8_t slaveAddress)
{
    UCB0CTL1 |= UCSWRST;
    UCB0I2CSA = slaveAddress;
    UCB0CTL1 &= ~UCSWRST;
}

uint8_t I2C_USCI_Write_Byte(uint8_t slaveAddress, uint8_t value)
{
    while(UCB0CTL1 & UCTXSTP);
    UCB0CTL1 |= UCTR | UCTXSTT;

    while(!(IFG2 & UCB0TXIFG));
    
    if(UCB0STAT & UCNACKIFG) 
    {
        return UCB0STAT;
    }

    UCB0TXBUF = slaveAddress;

    while(!(IFG2 & UCB0TXIFG));

    if(UCB0STAT & UCNACKIFG) 
    {
        return UCB0STAT;
    }

    UCB0TXBUF = value;

    while(!(IFG2 & UCB0TXIFG));

    if(UCB0STAT & UCNACKIFG) 
    {
        return UCB0STAT;
    }

    UCB0CTL1 |= UCTXSTP;
    IFG2 &= ~UCB0TXIFG;

    return 0;
}

uint8_t I2C_USCI_Read_Byte(uint8_t slaveAddress)
{
    while(UCB0CTL1 & UCTXSTP);
    UCB0CTL1 |= (UCTR | UCTXSTT);

    while(!(IFG2 & UCB0TXIFG));
    UCB0TXBUF = slaveAddress;

    while(!(IFG2 & UCB0TXIFG));
    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTT;
    IFG2 &= ~UCB0TXIFG;

    while(UCB0CTL1 & UCTXSTT);
    UCB0CTL1 |= UCTXSTP;

    return UCB0RXBUF;
}

uint8_t I2C_USCI_Read_Word(uint8_t slaveAddress, uint8_t *data, uint8_t length)
{
    uint8_t i = 0;

    while(UCB0CTL1 & UCTXSTP);
    UCB0CTL1 |= UCTR | UCTXSTT;

    while(!(IFG2 & UCB0TXIFG));
    IFG2 &= ~UCB0TXIFG;
    
    if(UCB0STAT & UCNACKIFG) 
    {
        return UCB0STAT;
    }

    UCB0TXBUF = slaveAddress;

    while(!(IFG2 & UCB0TXIFG));
    
    if(UCB0STAT & UCNACKIFG) 
    {
        return UCB0STAT;
    }

    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTT;
    IFG2 &= ~UCB0TXIFG;
    
    while(UCB0CTL1 & UCTXSTT);

    for(i = 0; i < (length - 1); i++)
    {
        while(!(IFG2&UCB0RXIFG));
        IFG2 &= ~UCB0TXIFG;
        data[i] = UCB0RXBUF;
    }

    while(!(IFG2 & UCB0RXIFG));
    IFG2 &= ~UCB0TXIFG;
    UCB0CTL1 |= UCTXSTP;
    data[length - 1] = UCB0RXBUF;
    IFG2 &= ~UCB0TXIFG;

    return 0;
}