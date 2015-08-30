/**
 *	file: assembler.c
 *	author: matthew.james.bird@gmail.com
 *
 *	assembler for the hack assembly language.
 *
 *	usage: assembler source output
 */

#include <stdio.h>
#include <stdbool.h>	// bool type
#include <ctype.h>		// isspace()

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
	
	// main read loop
	char c;
	bool comment = false;
	bool content = false;	// whether there is content on the current line
	while ((c = fgetc(source)) != EOF)
	{
		if (c == '/')
		{
			comment = true;
		}
		else if (c == '\n')
		{
			if (content)	// only print newlines if there was content on that line
			{
				fputc('\n', out);
			}
			comment = false;	// newline breaks comments
			content = false;
		}
		else if (isspace(c))
		{
			continue;
		}
		else if (!comment)
		{
			fputc(c, out);
			content = true;
		}
	}
	fputc('\n', out);
}