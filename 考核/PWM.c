#include <STC89C5xRC.H>

void PWM_Init()
{
		TMOD &= 0xF0;    // 清零 T0 低4位
    TMOD |= 0x01;    // T0 模式1，16位定时器
    TH0 = (65536 - 92) / 256; // 定时器初值=65536-(定时时间(us)*晶振频率(MHz)/12)，定时100us
    TL0 = (65536 - 92) % 256;
		TF0=0;	//TimerFlag,溢出标志，由硬件自动置位和清除
    ET0 = 1;	// 允许 T0 中断
    EA = 1;	// 总中断使能
    TR0 = 1;	// 启动 T0
}
/**
sbit servo1=P1^0;
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
**/