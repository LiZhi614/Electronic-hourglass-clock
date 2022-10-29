#ifndef __I2C_H_
#define __I2C_H_
#include <reg52.h>

sbit SCL=P2^4;
sbit SDA=P2^5;

void Delay10us();
void I2cStart();
void I2cStop();
unsigned char I2c_SendByte(unsigned char dat);
unsigned char I2c_ReadByte();

#endif