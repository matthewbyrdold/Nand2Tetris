#include <stdio.h>
#include <stdlib.h>

/** 
itob: converts v to binary form.
*/
void itob(int v)
{
	int i;
	for (i = 15; i >= 0; i--)
		putchar('0' + ((v >> i) & 1));
}

int main(void)
{	
	
}