/**
 *	file: assembler.c
 *	author: matthew.james.bird@gmail.com
 *
 *	calls the assembler for the hack assembly language.
 * 
 * 	usage: assembler source output
 *
 */

#include "assemble.h"

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
		fprintf(stderr, "Error: cannot open source file %s\n", argv[1]);
		return 1;
	}
	
	// open output file
	FILE* output = fopen(argv[2], "wb");
	if (output == NULL)
	{
		fprintf(stderr, "Error: cannot open output file %s\n", argv[2]);
		fclose(source);
		return 1;
	}
	
	// assembler call
	if (assemble(source, output) == false)
	{
		fprintf(stderr, "Quitting with error.\n");
		return 1;
	}
	return 0;
}

