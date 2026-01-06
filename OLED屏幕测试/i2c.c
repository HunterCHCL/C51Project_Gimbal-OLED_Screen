#include <STC89C5xRC.H>
#include "delay.h"

sbit I2C_SDA = P3^2;
sbit I2C_SCL = P3^3;

void I2C_Start()
{
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
}

void I2C_Stop()
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i = 0;
	for(i = 0; i < 8; ++i)
	{
		I2C_SDA = Byte & (0x80 >> i);
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}
unsigned char I2C_ReceiveByte()
{
	unsigned char Byte = 0, i;
	I2C_SDA = 1;
	for(i = 0; i < 8; ++i)
	{
		I2C_SCL = 1;
		if(I2C_SDA)	Byte |= (0x80 >> i);
		I2C_SCL = 0;
	}
	return Byte;
}
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SCL = 0;
}
unsigned char I2C_ReceiveAck()
{
	unsigned char Ack;
	I2C_SDA = 1;
	I2C_SCL = 1;
	Ack = I2C_SDA;
	I2C_SCL = 0;
	return Ack;
}