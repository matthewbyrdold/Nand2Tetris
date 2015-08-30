/**
 *	file: assembler.c
 *	author: matthew.james.bird@gmail.com
 *
 *	assembler for the hack assembly language.
 *
 *	usage: assembler source output
 */

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

int main(int argc, char* argv[])
{
	// check input is correct
	if (argc != 3)
	{
		fprintf(stderr, "Usage: assembler source output\n");
		return 1;
	}
	
	// open source file
	FILE* source = fopen(argv[1], "rb");
	if (source == NULL)
	{
		fprintf(stderr, "Error: cannot open source file %s", argv[1]);
		return 1;
	}
	
	// open output file
	FILE* out = fopen(argv[2], "wb");
	if (out == NULL)
	{
		fprintf(stderr, "Error: cannot open output file %s", argv[2]);
		fclose(source);
		return 1;
	}
	
	
}