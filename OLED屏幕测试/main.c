#include <STC89C5xRC.H>
#include "OLED.h"
#include "OLED_Font.h"
#include "keyboard.h"
#include "delay.h"
unsigned int menuIndex=0
void GUI(unsigned int key)//UI选择
{
	if(key!=1&&key!=2&&key!=11){return;}
    OLED_Clear();
    if(menuIndex==0)//初始界面
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
    OLED_Init();
    OLED_Clear();
    delay(1000);
    OLED_ShowChar(1, 1, 't');
    P21 = 0;
    OLED_ShowString(1, 2, "Test");
    OLED_ShowNum(2, 1, 123456, 6);
	GUI(3);
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
					GUI(key);
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