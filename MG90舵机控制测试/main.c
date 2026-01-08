#include <STC89C5xRC.H>
#include "delay.h"
#include "PWM.h"
#include "UART.h"

sbit servo1=P2^1;//SG90接收20ms周期的脉冲，占空比从2.5%(1/40)到12.5%(1/8)线性对应0°到180°，每增加2.5%转45°,增加1/1800增加1°
unsigned int servo1_Angle=0; //5代表0°，每增加45°增加5(即占空比增加2.5%),允许值从5到25
unsigned char buf[5]={0};
unsigned int bufCounter=0,Counter=0;

void Timer_Routine() interrupt 1
{
	TL0 = (65536 - 92) % 256;		//设置定时初值
	TH0 = (65536 - 92) / 256;
	Counter++;
	Counter %= 200; //重置counter,现在的值是200,即20ms

	if(Counter < (servo1_Angle/12)+5)//神秘舵机从0.5ms到2ms转180度，跟说明书不一样
	{
		servo1 = 1;
	}
	else
	{
		servo1 = 0;
	}
}
void adjustDutyCycle()
{
	unsigned int i;
	unsigned int dat=0;
	for(i=1;buf[i]!='E';i++)
	{
		dat*=10;
		dat+=buf[i]-'0';
	}
	if(dat<=180&&dat>=0)
	{
		servo1_Angle=dat;
	}
}
void UART_Routine() interrupt 4
{
	if(RI == 1)//检测是否是接收数据中断
	{
		if(SBUF=='S'){bufCounter=0;}
		buf[bufCounter]=SBUF;
		bufCounter++;
		if(SBUF=='E'){adjustDutyCycle();UART_SendStr(buf);}
		//UART_SendByte(SBUF);
		RI = 0;//软件置0
	}
	
}

void main()
{
	UART_Init();
	PWM_Init();
	while(1)
	{
		UART_SendByte(servo1_Angle/100+'0');
		UART_SendByte((servo1_Angle%100)/10+'0');
		UART_SendByte(servo1_Angle%10+'0');
		//UART_SendStr(buf);
		delay(500);
	}
}