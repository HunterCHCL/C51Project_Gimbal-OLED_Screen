#include <STC89C5xRC.H>
#include "delay.h"

void UART_Init()//9600bps
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;			//设置定时初始值
	TH1 = 0xFD;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	//中断开关
	ES = 1;			//串口中断开关
	EA = 1;			//总中断开关
}

	void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(TI == 0);//数据发送完，硬件置1
	TI = 0;		//软件置0
}
/**
void UART_Routine() interrupt 4
{
	if(RI == 1)//检测是否是接收数据中断
	{
		//检测到中断后的动作

		UART_SendByte(SBUF);
		RI = 0;//软件置0
	}
}
**/
void UART_SendStr(unsigned char *str)
{
	while(*str!='\0')
	{
		UART_SendByte(*str);
		str++;
	}
}