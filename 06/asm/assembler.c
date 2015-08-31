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
#include <ctype.h>		// isspace(), isdigit()
#include <stdlib.h>		// atoi()
#include <string.h>		// strcpy()

#define MAX_A 32767

/** 
*	decodeA: reads in an A instruction from source, and outputs the a-instruction to out, converted to binary.
*	returns source line number
*/
int decodeA(FILE* source, FILE* output, int line)
{
	char* number = malloc(6); //holds the number in the @instruction
	if (number == NULL)
	{
		fprintf(stderr, "Error (decodeA): cannot malloc number\n");
	}
	
	// read in the @ instruction
	int i = 0;
	char c;
	while ((c = fgetc(source)) && isdigit(c))
	{
		if (i > 4)
		{
			fprintf(stderr, "Error (line %d): integer too large\n", line);
		}
		number[i++] = c;
	}
	if (i == 0)
	{
		fprintf(stderr, "Error (line %d): expected value after @\n", line);
	}
	number[i] = '\0';
	
	// convert the @ instruction to int
	int v = atoi(number);
	free(number);
	if (v > MAX_A)	
	{
		fprintf(stderr, "Error (line %d): integer too large\n", line);
	}
	
	// output the a-instruction converted to binary
	for (i = 15; i >= 0; i--)
		fputc('0' + ((v >> i) & 1), output);
	
	// carry on reading until newline
	while (c != '\n' && c != EOF)
	{
		c = fgetc(source);
	}
	if (c == '\n')
	{
		fputc('\n', output);
		line++;
	}
	
	return line;
}

/** 
*	decodeC: reads in a C instruction from source, and outputs the C-instruction to out, converted to binary.
*	returns line number.
*/
int decodeC(FILE* source, FILE* output, int line)
{
	// C-instructions have three parts: dest, comp, and jump.
	char* dest = malloc(4);
	char* comp = malloc(4);
	char* jump = malloc(4);
	if (dest == NULL || dest == NULL || jump == NULL)
	{
		fprintf(stderr, "Error (line: %d): cannot malloc\n", line);
	}
	
	char c;
	char* buffer = malloc(4);
	int i = 0;
	bool dest = false;
	bool comp = false;
	bool jump = false;
	while ((c = fgetc(source)) != EOF)
	{
		if (i > 3)
		{
			fprintf(stderr, "Error (line: %d): invalid instruction\n", line);
		}
		else if (c == '=')	// buffer is dest
		{
			// strcpy buffer to dest
			// dest = true
			// set i = 0
		}
		else if ((c == '\n' && !comp) || c == ';')	// buffer is comp
		{
			// strcpy buffer to dest
			// comp = true
			// set i = 0
		}
		else if (c == '\n' && comp)	// buffer is jump
		{
			// strcpy buffer to jump
			// jump = true
			// set i = 0
		}
		if (c == '\n')
		{
			line++;
			break;
		}
		if (c == '/')
		{
			break;
		}
		// ...
		// buffer[i++] = c;
	}
	
	// write C-instruction code (111)
	// write comp (if comp and not in table, error)
	// write dest
	// write jump
	
	free(dest);
	free(comp);
	free(jump);
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
	FILE* output = fopen(argv[2], "wb");
	if (output == NULL)
	{
		fprintf(stderr, "Error: cannot open output file %s", argv[2]);
		fclose(source);
		return 1;
	}
	
	// main read loop
	char c;
	bool comment = false;	// are we in a comment?
	int line = 1;	// source line number
	int i; 		// reusable iterator
	while ((c = fgetc(source)) != EOF)
	{
		if (c == '/')
		{
			comment = true;
		}
		else if (c == '\n')
		{
			line++;
			comment = false;	// newline breaks comments
		}
		else if (isspace(c))
		{
			continue;
		}
		else if (comment) 
		{
			continue;	// skip comments
		}
		else if (c == '@')	// A-INSTRUCTION
		{
			line = decodeA(source, output, line);
		}
		else 				// C-INSTRUCTION (or invalid)
		{
			line = decodeC(source, output, line);
		}
	}
}