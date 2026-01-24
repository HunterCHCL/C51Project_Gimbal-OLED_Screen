#include <STC89C5xRC.H>
#include "OLED.h"
#include "delay.h"
#include "PWM.h"
#include "Keyboard.h"
#include "UART.h"
#include "OLED_Font.h"
#define addDeg 45
#define delTime 25
unsigned int menuIndex = 0, servoHAngle = 90, bufCounter = 0, Counter = 0, drawLineFlag = 0, drawLineLen = 0;
//unsigned int  servoVAngle = 90;
unsigned char buf[10] = {0};
sbit servoMotorH = P2 ^ 1;
//sbit servoMotorV = P2 ^ 2;
void adjustAngle(unsigned int TGTAngle, unsigned int *currentAngle, unsigned int del) reentrant // 缓慢转动云台
{
	if (TGTAngle < *currentAngle)
	{
		while (*currentAngle - TGTAngle >= 12)
		{
			*currentAngle -= 12;
			UART_SendByte(*currentAngle / 100 + '0');
			UART_SendByte((*currentAngle % 100) / 10 + '0');
			UART_SendByte(*currentAngle % 10 + '0');
			delay(del);
		}
	}
	if (TGTAngle > *currentAngle)
	{
		while (TGTAngle - *currentAngle >= 12)
		{
			*currentAngle += 12;
			UART_SendByte(*currentAngle / 100 + '0');
			UART_SendByte((*currentAngle % 100) / 10 + '0');
			UART_SendByte(*currentAngle % 10 + '0');
			delay(del);
		}
	}
}
void drawLine(unsigned int len) // 画直线
{
	if (len == 0)
	{
		return;
	}
	/**
	UART_SendByte(len);
	adjustAngle(90, &servoHAngle, delTime);
	delay(500);
	adjustAngle(90 - len, &servoHAngle, delTime);
	delay(500);
	adjustAngle(90 + len, &servoHAngle, delTime);
	delay(500);
	adjustAngle(90, &servoHAngle, delTime);
	UART_SendByte(servoHAngle+'0');
	**/
	servoHAngle=90;
	delay(100);
	servoHAngle=90-len;
	delay(100);
	servoHAngle=90+len;
	delay(100);
	servoHAngle=90;
}
/**
void drawTiltedLine(unsigned int ang,unsigned int *H,unsigned int *V,unsigned int del,unsigned char v)//画45度线
{
	if(ang < *H)
	{
		while(*H - ang >= 12)
		{
			*H -= 12;
			if(v=='u')
			{*V += 12;}
			else{*V -= 12;}
			delay(del);
		}
	}
	if(ang > *H)
	{
		while(ang - *H >= 12)
		{
			*H += 12;
			if(v=='u')
			{*V += 12;}
			else{*V -= 12;}
			delay(del);
		}
	}
}

void adjustDutyCycle()//调整电机角度
{
	unsigned int i,dat=0;
	for(i=2;buf[i]!='V';i++)
	{
		dat*=10;
		dat+=buf[i]-'0';
	}
	if(dat>=0&&dat<=180)
	{
		adjustAngleUART(dat,&servoHAngle,500);
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
		adjustAngleUART(dat,&servoVAngle,500);
	}
}
**/
unsigned int dataProcess()
{
	unsigned int i, dat = 0;
	for (i = 1; buf[i] != 'E'; i++)
	{
		dat *= 10;
		dat += buf[i] - '0';
	}
	UART_SendByte(dat / 100 + '0');
	UART_SendByte((dat % 100) / 10 + '0');
	UART_SendByte(dat % 10 + '0');
	if (dat <= 180 && dat >= 0)
	{
		return dat;
	}
	return 0;
}
void UART_Routine() interrupt 4
{
	if (RI == 1) // 检测是否是接收数据中断
	{
		// 接收数据并写入字符串
		if (SBUF == 'S')
		{
			bufCounter = 0;
		}
		buf[bufCounter] = SBUF;
		bufCounter++;
		if (SBUF == 'E')
		{
			if (menuIndex == 1)
			{
				drawLineLen = dataProcess();
				drawLineFlag = 1;
			}
			UART_SendStr(buf);
		}
		RI = 0; // 软件置0
	}
}

void Timer_Routine() interrupt 1
{
	TL0 = (65536 - 92) % 256; // 设置定时初值
	TH0 = (65536 - 92) / 256;
	Counter++;
	Counter %= 200; // 重置counter,现在的值是200,即20ms

	if (Counter < (servoHAngle / 12 + 5)) // 神秘舵机从0.5ms到2ms转180度
	{
		servoMotorH = 1;
	}
	else
	{
		servoMotorH = 0;
	}
	/**
	if (Counter < (servoVAngle / 12) + 5) // 神秘舵机从0.5ms到2ms转180度，要除以12
	{
		servoMotorV = 1;
	}
	else
	{
		servoMotorV = 0;
	}
	**/
}
/**
void drawTri()
{
	adjustAngle(90,&servoHAngle,500);
	adjustAngle(110,&servoVAngle,500);
	adjustAngle(70,&servoHAngle,500);
	drawTiltedLine(90,&servoHAngle,&servoVAngle,500,'u');
	drawTiltedLine(70,&servoHAngle,&servoVAngle,500,'d');
	adjustAngle(90,&servoHAngle,500);
}
void drawTriWLen()
{
	adjustAngle(90,&servoHAngle,500);
	adjustAngle(45,&servoVAngle,500);
	adjustAngle(45,&servoHAngle,500);
	drawTiltedLine(90,&servoHAngle,&servoVAngle,500,'u');
	drawTiltedLine(135,&servoHAngle,&servoVAngle,500,'d');
	adjustAngle(90,&servoHAngle,500);
}
**/
void GUILogic(unsigned int key) // UI逻辑
{
	if (menuIndex == 0) // 初始界面
	{
		if (key == 2)
		{
			menuIndex = 2;
			return;
		}
		if (key == 1)
		{
			menuIndex = 1;
			return;
		}
	}
	if (menuIndex == 1)
	{
		if (key == 11)
		{
			menuIndex = 0;
			return;
		}
	}
	if (menuIndex == 2)
	{
		if (key == 2)
		{
			if (servoHAngle - addDeg >= 0&& servoHAngle - addDeg <= 180)
			{
				servoHAngle -= addDeg;
				//adjustAngle(servoHAngle - addDeg, &servoHAngle, delTime);
			}
			return;
		}
		if (key == 1)
		{
			if (servoHAngle + addDeg <= 180&& servoHAngle + addDeg >= 0)
			{
				servoHAngle += addDeg;
				//adjustAngle(servoHAngle + addDeg, &servoHAngle, delTime);
			}
			return;
		}
		if (key == 11)
		{
			menuIndex = 0;
			return;
		}
	}
}
void drawGUI() // 显示UI,画的时候临时禁用中断不然画的非常慢
{
	EA = 0;
	OLED_Clear();
	if (menuIndex == 0) // 初始界面
	{
		OLED_ShowString(1, 1, "  Modes:");
		OLED_ShowString(2, 1, "1.draw Line");
		OLED_ShowString(3, 1, "2.Manual Angle");
	}
	if (menuIndex == 1) // UART控制画线
	{
		OLED_ShowString(1, 1, "   UART");
		OLED_ShowString(2, 1, "Controlling");
	}
	if (menuIndex == 2) // 按键控制舵机角度
	{
		OLED_ShowString(1, 1, "Angle:");
		OLED_ShowNum(1, 7, servoHAngle, 3);
		OLED_ShowString(2, 1, "1.add 45deg");
		OLED_ShowString(3, 1, "2.subtract 45deg");
	}
	EA = 1;
}
void main()
{
	unsigned int keyDown = 0;
	unsigned int key = 0;
	OLED_Init();
	PWM_Init();
	UART_Init();
	drawGUI();
	while (1)
	{
		if (drawLineFlag)
		{
			drawLineFlag = 0;
			drawLine(drawLineLen);
		}
		if (keyDown == 0)
		{
			key = scanKeyPress();
			keyDown = key;
			if (key != 0)
			{
				GUILogic(key);
				drawGUI();
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