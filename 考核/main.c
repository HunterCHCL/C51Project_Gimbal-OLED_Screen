#include <STC89C5xRC.H>
#include "OLED.h"
#include "delay.h"
#include "PWM.h"
#include "Keyboard.h"
#include "UART.h"
#include "OLED_Font.h"
unsigned int menuIndex=0,servoH_Angle=90,servoV_Angle=90,bufCounter=0,Counter=0;
unsigned char buf[10]={0};
sbit servoMotorH= P2^2;
sbit servoMotorV= P2^1;
void adjustAngle(unsigned int TGTAngle,unsigned int *currentAngle,unsigned int del)//缓慢转动云台
{
	if(TGTAngle < *currentAngle)
	{
		while(*currentAngle - TGTAngle >= 12)
		{
			*currentAngle -= 12;
			delay(del);
		}
	}
	if(TGTAngle > *currentAngle)
	{
		while(TGTAngle - *currentAngle >= 12)
		{
			*currentAngle += 12;
			delay(del);
		}
	}
}
void adjustDutyCycle()
{
	unsigned int i,dat=0;
	for(i=2;buf[i]!='V';i++)
	{
		dat*=10;
		dat+=buf[i]-'0';
	}
	if(dat>=0&&dat<=180)
	{
		adjustAngle(dat,&servoH_Angle,500);
	}
	dat=0;
	while(buf[i]!='E')
	{
		i++;
		dat*=10;
		dat+=buf[i]-'0';
	}
	if(dat>=0&&dat<=180)
	{
		adjustAngle(dat,&servoV_Angle,500);
	}
}
void UART_Routine() interrupt 4
{
	if(RI == 1)//检测是否是接收数据中断
	{
		//接收数据并写入字符串
		if(SBUF=='S'){bufCounter=0;}
		buf[bufCounter]=SBUF;
		bufCounter++;
		if(SBUF=='E')
		{
			if(menuIndex==2){adjustDutyCycle();}
			UART_SendStr(buf);
		}
		UART_SendByte(SBUF);
		RI = 0;//软件置0
	}
}

void Timer_Routine() interrupt 1
{
	TL0 = (65536 - 92) % 256;		//设置定时初值
	TH0 = (65536 - 92) / 256;
	Counter++;
	Counter %= 200; //重置counter,现在的值是200,即20ms

	if(Counter < (servoH_Angle/12)+5)//神秘舵机从0.5ms到2ms转180度，跟说明书不一样
	{servoMotorH = 1;}
	else
	{servoMotorH = 0;}
	if(Counter < (servoV_Angle/12)+5)//神秘舵机从0.5ms到2ms转180度，跟说明书不一样，要除以12
	{servoMotorV = 1;}
	else
	{servoMotorV = 0;}
}
void drawTri()
{
	
}
void drawTriWLen()
{
	
}
void GUI(unsigned int key)//UI选择
{
    OLED_Clear();
    if(menuIndex==0)
    {
			if(key==2){menuIndex=1;}
			if(key==1){menuIndex=2;}
        OLED_ShowString(0,0,"Choose Mode");
			OLED_ShowString(1,0,"1.UART mode");
			OLED_ShowString(2,0,"2.AUTO mode");
    }
		if(menuIndex==1)
		{
			OLED_ShowString(0,0,"1.draw Tri");
			OLED_ShowString(1,0,"2.draw Tri");
			OLED_ShowString(2,0,"/w length");
			if(key==2){drawTri();}
			if(key==1){drawTriWLen();}
			if(key==11){menuIndex=0;}
		}
		if(menuIndex==2)
		{
			OLED_ShowString(0,0,"UART control");
			OLED_ShowString(1,0,"mode");
			if(key==11){menuIndex=0;}
		}
		
}
void main()
{
	unsigned int keyDown = 0;
    unsigned int key = 0;
    unsigned int mode=1;//0代表UART控制舵机，1代表自动云台
    OLED_Init();
    OLED_Clear();
	PWM_Init();
	UART_Init();
	GUI(0);
    while (1)
    {
        if (keyDown == 0)
        {
            key = scanKeyPress();
            keyDown = key;
            if (key != 0)
            {
                GUI(key);
            }
        }
        else
        {
            if (scanKeyRelease(keyDown) == 0)
            {
                keyDown = 0;
                key = 0;
            }
        }
    }
}