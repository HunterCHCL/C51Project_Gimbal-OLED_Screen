#include <intrins.h>

void delay(unsigned int x)	//@11.0592MHz
{
	unsigned char data i, j;
while(x>0)
{
	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
	x--;
}
}
