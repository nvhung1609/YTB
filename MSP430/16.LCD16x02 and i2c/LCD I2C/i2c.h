#ifndef	I2C_H_
#define	I2C_H_

#include <stdint.h>
#include <msp430.h>

void I2C_USCI_Init(uint8_t slaveAddress);
void I2C_USCI_Set_Address(uint8_t slaveAddress);
uint8_t I2C_USCI_Write_Byte(uint8_t slaveAddress, uint8_t value);
uint8_t I2C_USCI_Read_Byte(uint8_t slaveAddress);
uint8_t I2C_USCI_Read_Word(uint8_t slaveAddress, uint8_t *data, uint8_t length);

#endif /* I2C_H_ */