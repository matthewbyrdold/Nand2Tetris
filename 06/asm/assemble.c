/**
 *	file: assemble.c
 *	author: matthew.james.bird@gmail.com
 *
 *	assembler for the hack assembly language.
 *
 *	usage: assembler source output
 */

#include "assemble.h"
#include <stdio.h>
#include <stdbool.h>	// bool type
#include <ctype.h>		// isspace(), isdigit()
#include <stdlib.h>		// atoi()
#include <string.h>		// strcpy(), strcmp(), strchr()


// head for symbol dictionary linked list
symNode* symHead;

// table for comp codes and their translations
compNode* compDict[COMP_TABLE_SIZE];

// table for jump codes and their translations
jumpNode* jumpDict[JUMP_TABLE_SIZE];

const char* compCodes[COMP_TABLE_SIZE] = {"0", "1", "-1", "D", "A", "!D", "!A", "-D", "-A",
											"D+1", "A+1", "D-1", "A-1", "D+A", "D-A", "A-D",
											"D&A", "D|A", "M", "!M", "-M", "M+1", "M-1", "D+M",
											"D-M", "M-D", "D&M", "D|M"};
	
const char* compTranslations[COMP_TABLE_SIZE] = {"0101010", "0111111", "0111010", "0001100",
												"0110000", "0001101", "0110001", "0001111",
												"0110011", "0011111", "0110111", "0001110",
												"0110010", "0000010", "0010011", "0010011",
												"0000000", "0010101", "1110000", "1110001",
												"1110011", "1110111", "1110010", "1000010",
												"1010011", "1000111", "1000000", "1010101"};

const char* jumpCodes[JUMP_TABLE_SIZE] = {"JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP"};

const char* jumpTranslations[JUMP_TABLE_SIZE] = {"001", "010", "011", "100", "101", "110", "111"};

/**
 *	addSym: add the symbol-translation pair to the start of the linked list beginning with head.
 *	returns true on success, else false;
 */
bool addSym(const char* symbol, const char* translation, int line)
{
	// construct the new node
	symNode* temp = malloc(sizeof(symNode));
	if (temp == NULL)
	{
		fprintf(stderr, "Error (line %d): cannot malloc new symbol node.\n", line);
		return false;
	}
	strcpy(temp->symbol, symbol);
	strcpy(temp->translation, translation);
	
	if (symHead != NULL)	// list not empty
	{
		temp->next = symHead;
	}
	symHead = temp;
	return true;
}

/**
 *	buildTables: builds the table for comp/jump codes and their translations.
 */
bool buildTables(void)
{
	int i;
	
	// build comp table
	for (i = 0; i < COMP_TABLE_SIZE; i++)
	{
		compNode* temp = malloc(sizeof(compNode));
		if (temp == NULL)
		{
			fprintf(stderr, "Error: cannot create comp table\n");
			return false;
		}
		strcpy(temp->entry, compCodes[i]);
		strcpy(temp->translation, compTranslations[i]);
		compDict[i] = temp;
	}
	
	// build jump table
	for (i = 0; i < JUMP_TABLE_SIZE; i++)
	{
		jumpNode* temp = malloc(sizeof(jumpNode));
		if (temp == NULL)
		{
			fprintf(stderr, "Error: cannot create jump table\n");
			return false;
		}
		strcpy(temp->entry, jumpCodes[i]);
		strcpy(temp->translation, jumpTranslations[i]);
		jumpDict[i] = temp;
	}
	
	// load default register symbols into symbol table
	int v;
	int k;
	int j;
	for (i = 0; i < 16; i++)
	{
		char* tempSym = malloc(4);
		if (tempSym == NULL)
		{
			fprintf(stderr, "Error: cannot create register table\n");
			return false;
		}
		
		char* tempTran = malloc(17);
		if (tempTran == NULL)
		{
			fprintf(stderr, "Error: cannot create register table\n");
			return false;
		}
		
		tempSym[0] = 'R';
		sprintf(tempSym+1, "%d", i);
		v = i;
		k = 0;
		for (j = 15; j >= 0; j--, k++)
		{
			tempTran[k] = '0' + ((v >> j) & 1);		
		}
		tempTran[k] = '\0';
		if (addSym(tempSym, tempTran, 0) == false)
		{
			fprintf(stderr, "Error: cannot create register table\n");
			return false;
		}
	}
	return true;
}

/**
 *	clearTables: frees the tables of comp/jump codes and their translations.
 */
void clearTables(void)
{
	// clear computations table
	int i;
	for (i = 0; i < COMP_TABLE_SIZE; i++)
	{
		free(compDict[i++]);
	}
	
	// clear jump table
	for (i = 0; i < JUMP_TABLE_SIZE; i++)
	{
		free(jumpDict[i++]);
	}
	
	// clear symbol table
	symNode* pos = symHead;
	symNode* next;
	while (pos != NULL)
	{
		next = pos->next;
		free(pos);
		pos = next;
	}
}

/** 
 *	decodeA: reads in an A instruction from source, and outputs the a-instruction to out, converted to binary.
 *	returns source line number, or -1 if error.
*/
int decodeA(FILE* source, FILE* output, int line)
{
	static int varNum = 16;
	
	char* instruction = malloc(MAX_SYMBOL_SIZE + 1); //holds the number in the @instruction
	if (instruction == NULL)
	{
		fprintf(stderr, "Error (decodeA): cannot malloc instruction\n");
		return -1;
	}
	
	// read in the @ instruction
	int i = 0;
	char c;
	if ((c = fgetc(source)) && !isdigit(c))		// symbol
	{
		do
		{
			if (i > MAX_SYMBOL_SIZE)
			{
				fprintf(stderr, "Error (line %d): symbol too large (max length %d chars)\n", line, MAX_SYMBOL_SIZE);
				return -1;
			}
			instruction[i++] = c;
		} while ((c = fgetc(source)) && !isspace(c) && c != EOF);
			
		if (i == 0)
		{
			fprintf(stderr, "Error (line %d): expected value for A-instruction\n", line);
			return -1;
		}
		instruction[i] = '\0';
		
		// search table for instruction
		symNode* pos;
		for (pos = symHead; pos != NULL; pos = pos->next)
		{
			if (strcmp(instruction, pos->symbol) == 0)
			{
				fprintf(output, pos->translation);
				break;
			}
		}
		if (pos == NULL)		// symbol not in table: add it!
		{
			char* tempTran = malloc(17);
			int k = 0;
			int j;
			int v = varNum;
			for (j = 15; j >= 0; j--, k++)
			{
				tempTran[k] = '0' + ((v >> j) & 1);		
			}
			tempTran[k] = '\0';
			addSym(instruction, tempTran, 0);
			varNum++;
			// output symbol
			fprintf(output, tempTran);
			fputc('\n', output);
			return line;
		}
	}
	if (isdigit(c))		// non-symbolic a-instruction
	{
		do
		{
			if (i > 4)
			{
				fprintf(stderr, "Error (line %d): integer too large\n", line);
				return -1;
			}
			instruction[i++] = c;
		} while ((c = fgetc(source)) && isdigit(c));

		if (i == 0)
		{
			fprintf(stderr, "Error (line %d): expected value for A-instruction\n", line);
			return -1;
		}
		instruction[i] = '\0';

		// convert the @ instruction to int
		int v = atoi(instruction);
		free(instruction);
		if (v > MAX_A || v < 0)	
		{
			fprintf(stderr, "Error (line %d): %d is an invalid integer\n", line, v);
			return -1;
		}
		
		// output the a-instruction converted to binary
		for (i = 15; i >= 0; i--)
		{
			fputc('0' + ((v >> i) & 1), output);
		}
	}
				
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
 *	writeComp: translates comp and outputs it to output.
 *	returns true on success, else false.
 */
bool writeComp(char* comp, FILE* output)
{
	// search computations for the comp
	int i;
	for (i = 0; i < COMP_TABLE_SIZE; i++)
	{
		if (strcmp(compDict[i]->entry, comp) == 0)
		{
			// found
			fprintf(output, compDict[i]->translation);
			return true;
		}
	}
	// not found
	printf("%s not found\n", comp);
	return false;
}

/**
 *	writeJump: translates jump and outputs it to output.
 *	returns true on success, else false.
 */
bool writeJump(char* jump, FILE* output)
{
	// search jump table for the jump
	int i;
	for (i = 0; i < JUMP_TABLE_SIZE; i++)
	{
		if (strcmp(jumpDict[i]->entry, jump) == 0)
		{
			// found
			fprintf(output, jumpDict[i]->translation);
			return true;
		}
	}
	// not found
	return false;
}

/** 
 *	decodeC: reads in a C instruction from source (first char is c), and outputs the C-instruction to out, converted to binary.
 *	returns line number, or -1 on error.
*/
int decodeC(char c, FILE* source, FILE* output, int line)
{
	// C-instructions have three parts: dest, comp, and jump.
	char* dest = malloc(4);
	char* comp = malloc(4);
	char* jump = malloc(4);
	if (dest == NULL || dest == NULL || jump == NULL)
	{
		fprintf(stderr, "Error (line: %d): cannot malloc\n", line);
	}
	
	char* buffer = malloc(4);
	int i = 0;
	bool destIn = false;
	bool compIn = false;
	bool jumpIn = false;
	do
	{
		if (i > 3)
		{
			fprintf(stderr, "Error (line: %d): invalid instruction\n", line);
		}
		else if (c == '=')	// buffer is dest
		{
			strcpy(dest, buffer);
			dest[i] = '\0';
			destIn = true;
			i = 0;
		}
		else if ((((c == '\n') || (c == '/') || c == EOF) && !compIn) || c == ';')	// buffer is comp
		{
			strcpy(comp, buffer);
			comp[i] = '\0';
			compIn = true;
			i = 0;
		}
		else if (((c == '\n') || (c == '/') || c == EOF) && compIn)	// buffer is jump
		{
			strcpy(jump, buffer);
			jump[i] = '\0';
			jumpIn = true;
			i = 0;
		}
		else if (!isspace(c) && c != '/')
		{
			buffer[i++] = c;
		}
		if (c == '\n' || c == '/' || c == EOF)
		{
			break;
		}
	}
	while (c = fgetc(source));
	
	// write C-instruction code (111)
	fprintf(output, "111");
	
	if (compIn) 
	{
		if (writeComp(comp, output) == false)
		{
			fprintf(stderr, "Error (line: %d): cannot translate '%s'\n", line, comp);
			return -1;
		}
	}
	else
	{
		// write default comp code
		fprintf(output, "111101010");
	}
	
	if (destIn)
	{
		if (strchr(dest, 'A') != NULL)
		{
			fputc('1', output);
		}
		else
		{
			fputc('0', output);
		}
		if (strchr(dest, 'D') != NULL)
		{
			fputc('1', output);
		}
		else
		{
			fputc('0', output);
		}
		if (strchr(dest, 'M') != NULL)
		{
			fputc('1', output);
		}
		else
		{
			fputc('0', output);
		}
	}
	else
	{
		// write default dest
		fprintf(output, "000");
	}
	
	if (jumpIn)
	{
		if (writeJump(jump, output) == false)
		{
			fprintf(stderr, "Error (line: %d): cannot translate jump '%s'\n", line, jump);
			return -1;
		}
	}
	else
	{
		// write default jump
		fprintf(output, "000");
	}
	
	free(dest);
	free(comp);
	free(jump);
	free(buffer);
	
	fputc('\n', output);
	line++;
	return line;
}

/**
 *	loadLabels: populates the symbol dictionary with all of the labels in the file.
 *	returns true on success, else false.
 */
bool loadLabels(FILE* source)
{
	char* tempLabel;
	char* tempTran;
	int line = 0;
	bool definingLabel = false;	// are we defining a label?
	bool comment = false;	// are we in a comment?
	bool content = false; // is there content on the current line?
	bool addLabel = false; // should we add the current line to the label tag?
	int numLabels = 0;
	char c;
	int i = 0; // label pos
	while ((c = fgetc(source)) != EOF)
	{
		if (c == '/')
		{
			comment = true;
		}
		else if (c == '(' && !comment)	// new label		TODO: remove these && !comment
		{
			if (definingLabel)
			{
				fprintf(stderr, "Error (line %d): cannot enter '(' in label name\n", line);
				return false;
			}
			definingLabel = true;
			
			tempLabel = malloc(MAX_SYMBOL_SIZE + 1);
			if (tempLabel == NULL)
			{
				fprintf(stderr, "Error (line %d): cannot malloc tempLabel\n", line);
				return false;
			}
		}
		else if (c == ')' && !comment)
		{
			if (!definingLabel)
			{
				fprintf(stderr, "Error (line %d): cannot enter ')' outside label\n", line);
				return false;
			}			
			definingLabel = false;
			
			// add to dict
			tempLabel[i] = '\0';
			i = 0;
			addSym(tempLabel, "", line);
			addLabel = true;	// TODO: just have addLabel be numLabels > 0
			numLabels++;
		}
		else if (definingLabel && !comment)
		{
			if (isspace(c))
			{
				fprintf(stderr, "Error (line %d): cannot enter whitespace in label name\n", line);
				return false;
			}
			else
			{
				tempLabel[i++] = c;
			}
		}
		if (c == '\n')
		{
			comment = false;
			if (content)
			{
				line++;			// TODO: don't want to increment when we've done a label
			}
			content = false;
		}
		else if (!isspace(c) && !comment && !definingLabel && c != ')')
		{
			content = true;
			if (addLabel)
			{
				tempTran = malloc(17);
				int v = line;
				int k = 0;
				int j;
				for (j = 15; j >= 0; j--, k++)
				{
					tempTran[k] = '0' + ((v >> j) & 1);		
				}
				tempTran[k] = '\0';
				
				for (symNode* pos = symHead; numLabels > 0; numLabels--)
				{
					strcpy(pos->translation, tempTran);
					pos = pos->next;
				}
				addLabel = false;
			}
		}
	}
	if (addLabel)
	{
		tempTran = malloc(17);
		int v = line;
		int k = 0;
		int j;
		for (j = 15; j >= 0; j--, k++)
		{
			tempTran[k] = '0' + ((v >> j) & 1);		
		}
		tempTran[k] = '\0';
		
		for (symNode* pos = symHead; numLabels > 0; numLabels--)
		{
			strcpy(pos->translation, tempTran);
			pos = pos->next;
		}
	}
	
	// rewind the file
	fseek(source, 0, SEEK_SET);
	
	return true;
}


bool assemble(FILE* source, FILE* output)
{
	// build translation tables
	if (buildTables() == false)
	{
		fprintf(stderr, "Terminating program due to error\n");
		return 1;
	}
	
	if (loadLabels(source) == false)
	{
		fprintf(stderr, "Terminating program due to error\n"); 
		return 1;
	}
		
	// main read loop
	char c;
	bool comment = false;	// are we in a comment?
	bool label = false;		// are we in a label?
	int line = 1;	// source line number
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
		else if (c == '(')
		{
			label = true;
		}
		else if (c == ')')
		{
			label = false;
		}
		else if (label)
		{
			continue;
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
			line = decodeC(c, source, output, line);
		}
		if (line == -1)
		{
			fprintf(stderr, "Terminating assembly due to error\n");
			return false;
		}
	}
	
	// clear translation tables
	clearTables();
	
	fclose(source);
	fclose(output);
	
	printf("Assembly successful\n");
	return true;
}