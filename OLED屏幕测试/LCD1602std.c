#include <STC89C5xRC.H>
#include "delay.h"

sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_EN=P2^7;
#define LCD_Data P0
#define uint unsigned int
#define uchar unsigned char
void LCD_writeCMD(uchar cmd)
{
	LCD_RW=0;
	LCD_RS=0;
	LCD_Data=cmd;
	LCD_EN=1;
	delay(1);
	LCD_EN=0;
	delay(1);
}
void LCD_writeData(uchar cmd)
{
	LCD_RW=0;
	LCD_RS=1;
	LCD_Data=cmd;
	LCD_EN=1;
	delay(1);
	LCD_EN=0;
	delay(1);
}
void LCD_init()
{
	LCD_writeCMD(0x38);
	LCD_writeCMD(0x0C);
	LCD_writeCMD(0x06);
	LCD_writeCMD(0x01);
}
void LCD_clear()
{
	LCD_writeCMD(0x01);
}
void LCD_setCursor(uchar line,uchar col)
{
	if(line==1){LCD_writeCMD(0x80|(col-1));}
	else{LCD_writeCMD(0x80|(col-1)+0x40);}
}
void LCD_displayChar(uchar line,uchar col,uchar content)
{
	LCD_setCursor(line,col);
	LCD_writeData(content);
}
void LCD_displayString(uchar line,uchar col,uchar *string)
{
	unsigned int i;
	LCD_setCursor(line,col);
	for(i=0;string[i]!='\0';i++)
	{
		LCD_writeData(string[i]);
	}
}
int pospow(uint a,uint x)
{
	uint i,result=a;
	if(x==0){return 1;}
	for(i=1;i<x;i++)
	{
		result*=a;
	}
	return result;
}
void LCD_displayNum(uchar line,uchar col,uint num,uint len)
{
	uint i;
	LCD_setCursor(line,col);
	for(i=len;i>=1;i--)
	{
		LCD_writeData('0'+num/pospow(10,i-1)%10);
	}
}
void LCD_writePattern(uchar addr,uchar *pat)
{
	uint i;
	addr=addr<<3;

	for(i=0;i<8;i++)
	{
		LCD_writeCMD(0x40|addr+i);
		LCD_writeData(*pat++);
	}
}
void LCD_displayIntArray(uchar line,uchar col,uint *arr,uint len)
{
	uint i;
	LCD_setCursor(line,col);
	for(i=0;i<len;i++)
	{
		LCD_writeData('0'+arr[i]);
	}
}
unsigned char intToStr(int ld,unsigned char *str)//把ld转换为str，返回值是ld的长度
{
	unsigned char i;
	unsigned char len;
	unsigned char buf[11];
	if(ld<0){
		ld = -ld; // 如果是负数则取绝对值
		*str++ = '-'; //字符串第一位先赋值一个负符号
		len++;
	}
	do{
		buf[i++] = ld%10+'0'; // 取余运算获取最后一位，拼接上'0',转为ASCLL码
		ld /= 10; // 除以10向左移动1位
	}while(ld >0);
		len += i;
	while(i-- >0){
		*str++ = buf[i];
	}
	*str = '\0'; //字符串末尾加\0表示字符串的结尾
	return len;
}