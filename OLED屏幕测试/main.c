#include <STC89C5xRC.H>
#include "OLED.h"
#include "OLED_Font.h"
#include "keyboard.h"
#include "delay.h"
#include "PWM.h"
sbit servo1=P2^1;
unsigned int Counter,servo1_Angle=90;

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
unsigned int menuIndex=0;
void drawTri()
{
	
}
void drawTriWLen()
{
	
}
void GUILogic(unsigned int key)//UI逻辑
{
    if(menuIndex==0)//初始界面
    {
			if(key==2){menuIndex=1;return;}
			if(key==1){menuIndex=2;return;}
    }
		if(menuIndex==1)
		{
			if(key==2){drawTri();return;}
			if(key==1){drawTriWLen();return;}
			if(key==11){menuIndex=0;return;}
		}
		if(menuIndex==2)
		{
			if(key==11){menuIndex=0;return;}	
		}
		
}
void drawGUI()//显示UI
{
    EA=0;
    OLED_Clear();
    if(menuIndex==0)//初始界面
    {
			OLED_ShowString(1,1,"Modes:");
			OLED_ShowString(2,1,"1.UART");
			OLED_ShowString(3,1,"2.AUTO");
    }
		if(menuIndex==1)
		{
			OLED_ShowString(1,1,"1.Tri1");
			OLED_ShowString(2,1,"2.Tri2");
		}
		if(menuIndex==2)
		{
			OLED_ShowString(1,1,"UART");
			OLED_ShowString(2,1,"mode");
		}
    EA=1;
}
void main()
{
    unsigned int keyDown = 0;
    unsigned int key = 0;
    OLED_Init();
		PWM_Init();
    delay(1000);
    OLED_ShowChar(1, 1, 't');
    //P21 = 0;
    OLED_ShowString(1, 2, "Test");
    OLED_ShowNum(2, 1, 123456, 6);
		drawGUI();
    while (1)
    {
        if (keyDown == 0)
        {
            key = scanKeyPress();
            keyDown = key;
					/**
            if (key != 0)
            {
                OLED_ShowNum(3, 1, key, 2);
            }
					**/
					if(key!=0){GUILogic(key);drawGUI();}
        }
        else
        {
            if (scanKeyRelease(keyDown) == 0)
            {
                keyDown = 0;
                //OLED_clear();
                key = 0;
            }
        }
    }
}