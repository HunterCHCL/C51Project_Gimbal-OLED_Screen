#include "delay.h"
#include <STC89C5xRC.H>


int scankey()
{
		P1=0xFF;
		P13=0;
		if(P14==0){delay(20);while(P14==0);delay(20);return 13;}
		if(P15==0){delay(20);while(P15==0);delay(20);return 9;}
		if(P16==0){delay(20);while(P16==0);delay(20);return 5;}
		if(P17==0){delay(20);while(P17==0);delay(20);return 1;}
		P13=1;
		P12=0;
		if(P14==0){delay(20);while(P14==0);delay(20);return 14;}
		if(P15==0){delay(20);while(P15==0);delay(20);return 10;}
		if(P16==0){delay(20);while(P16==0);delay(20);return 6;}
		if(P17==0){delay(20);while(P17==0);delay(20);return 2;}
		P12=1;
		P11=0;
		if(P14==0){delay(20);while(P14==0);delay(20);return 15;}
		if(P15==0){delay(20);while(P15==0);delay(20);return 11;}
		if(P16==0){delay(20);while(P16==0);delay(20);return 7;}
		if(P17==0){delay(20);while(P17==0);delay(20);return 3;}
		P11=1;
		P10=0;
		if(P14==0){delay(20);while(P14==0);delay(20);return 16;}
		if(P15==0){delay(20);while(P15==0);delay(20);return 12;}
		if(P16==0){delay(20);while(P16==0);delay(20);return 8;}
		if(P17==0){delay(20);while(P17==0);delay(20);return 4;}
		return 0;
}
int scanKeyPress()
{
	P1=0xFF;
		P13=0;
		if(P14==0){delay(20);return 13;}
		if(P15==0){delay(20);return 9;}
		if(P16==0){delay(20);return 5;}
		if(P17==0){delay(20);return 1;}
		P13=1;
		P12=0;
		if(P14==0){delay(20);return 14;}
		if(P15==0){delay(20);return 10;}
		if(P16==0){delay(20);return 6;}
		if(P17==0){delay(20);return 2;}
		P12=1;
		P11=0;
		if(P14==0){delay(20);return 15;}
		if(P15==0){delay(20);return 11;}
		if(P16==0){delay(20);return 7;}
		if(P17==0){delay(20);return 3;}
		P11=1;
		P10=0;
		if(P14==0){delay(20);return 16;}
		if(P15==0){delay(20);return 12;}
		if(P16==0){delay(20);return 8;}
		if(P17==0){delay(20);return 4;}
		return 0;
}
int scanKeyRelease(unsigned int prev)
{
	unsigned int line;
	P1=0xFF;
	switch(prev){
		case 1:P13=0;line=7;break;
		case 2:P12=0;line=7;break;
		case 3:P11=0;line=7;break;
		case 4:P10=0;line=7;break;
		case 5:P13=0;line=6;break;
		case 6:P12=0;line=6;break;
		case 7:P11=0;line=6;break;
		case 8:P10=0;line=6;break;
		case 9:P13=0;line=5;break;
		case 10:P12=0;line=5;break;
		case 11:P11=0;line=5;break;
		case 12:P10=0;line=5;break;
		case 13:P13=0;line=4;break;
		case 14:P12=0;line=4;break;
		case 15:P11=0;line=4;break;
		case 16:P10=0;line=4;break;
	}
	if(line==4&&P14==0){return 1;}
	if(line==5&&P15==0){return 1;}
	if(line==6&&P16==0){return 1;}
	if(line==7&&P17==0){return 1;}
	delay(20);
	return 0;
}
/**
//这段放在主循环外,keyDown用来标记按键状态,key用来存储按键值
unsigned int keyDown=0;
unsigned int key=0;
**/

/**
//这段放在主循环里
if (keyDown == 0)
{
	key = scanKeyPress();
	keyDown = key;
}
else
{
	if (scanKeyRelease(keyDown) == 0)
	{
		keyDown = 0;
		LCD_clear();
	}
	key = 0;//放if外面，在按键未释放时清空key值防止重复记录
}
**/