#include <STC89C5xRC.H>
#include "OLED.h"
#include "OLED_Font.h"
#include "keyboard.h"
#include "delay.h"

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
    while (1)
    {
        if (keyDown == 0)
        {
            key = scanKeyPress();
            keyDown = key;
            if (key != 0)
            {
                OLED_ShowNum(3, 1, key, 2);
            }
        }
        else
        {
            if (scanKeyRelease(keyDown) == 0)
            {
                keyDown = 0;
                OLED_clear();
                key = 0;
            }
        }
    }
}