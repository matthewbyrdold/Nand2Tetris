/**
 *	file: assemble.c
 *	author: matthew.james.bird@gmail.com
 *
 *	assembler for the hack assembly language.
 *
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_A 32767
#define COMP_TABLE_SIZE 28
#define JUMP_TABLE_SIZE 7
#define MAX_SYMBOL_SIZE 10

// node for symbol and its translation
typedef struct symNode
{
	char symbol[MAX_SYMBOL_SIZE];
	char translation[17];
	struct symNode* next;
}
symNode;

// node for comp code and its translation
typedef struct compNode 
{
	char entry[4];
	char translation[8];
}
compNode;

// node for jump code and its translation
typedef struct jumpNode 
{
	char entry[4];
	char translation[4];
}
jumpNode;

/**
 * assemble: translates source assembly file into machine code.
 * returns true on success, else false;
 */
bool assemble(FILE* source, FILE* output);

/**
 *	addSym: add the symbol-translation pair to the start of the linked list beginning with head.
 *	returns true on success, else false.
 */
bool addSym(const char* symbol, const char* translation, int line);

/**
 *	buildTables: builds the table for comp/jump codes and their translations.
 *	returns true on success, else false.
 */
bool buildTables(void);

/**
 *	clearTables: frees the tables of comp/jump codes and their translations.
 */
void clearTables(void);

/** 
 *	decodeA: reads in an A instruction from source, and outputs the a-instruction to out, converted to binary.
 *	returns source line number, or -1 if error.
*/
int decodeA(FILE* source, FILE* output, int line);

/**
 *	writeComp: translates comp and outputs it to output.
 *	returns true on success, else false.
 */
bool writeComp(char* comp, FILE* output);

/**
 *	writeJump: translates jump and outputs it to output.
 *	returns true on success, else false.
 */
bool writeJump(char* jump, FILE* output);

/** 
 *	decodeC: reads in a C instruction from source (first char is c), and outputs the C-instruction to out, converted to binary.
 *	returns line number, or -1 on error.
*/
int decodeC(char c, FILE* source, FILE* output, int line);

/**
 *	loadLabels: populates the symbol dictionary with all of the labels in the file.
 *	returns true on success, else false;
 */
bool loadLabels(FILE* source);