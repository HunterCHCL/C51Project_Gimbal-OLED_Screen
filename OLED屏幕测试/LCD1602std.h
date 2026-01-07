#ifndef __LCD1602std_H__
#define __LCD1602std_H__

void LCD_init();
void LCD_clear();
void LCD_displayChar(unsigned char line,unsigned char col,unsigned char content);
void LCD_displayNum(unsigned char line,unsigned char col,unsigned int num,unsigned int len);
void LCD_displayString(unsigned char line,unsigned char col,unsigned char *string);
void LCD_setCursor(unsigned char line,unsigned char col);
void LCD_writePattern(unsigned char addr,unsigned char *pat);
void LCD_displayIntArray(unsigned char line,unsigned char col,unsigned int *arr,unsigned int len);
#endif
