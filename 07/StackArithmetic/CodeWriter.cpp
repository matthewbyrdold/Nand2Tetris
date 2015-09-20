/**
 *	file: CodeWriter.cpp
 *
 */

#include <iostream>
#include <fstream>

#include "CodeWriter.hpp"

using namespace std;


CodeWriter::CodeWriter(ofstream& file)
	: output(file)
{}
	
CodeWriter::~CodeWriter()
{
	// TODO
	// output.close();
}
	
/**	  Informs the code writer that the translation of a new VM file has started.  */
void CodeWriter::setFileName(string file)
{
	fileName = file;
}

/**   Writes the assembly code that is the translation of the given arithmetic command.  */
void CodeWriter::writeArithmetic(string command)
{
	//TODO finish options
	if (command == "add")
	{
		popD();
		decSP();
		output << "M = D+M" << endl;
		incSP();
	}
	else if (command == "sub")
	{
		popD();
		decSP();
		output << "M = M-D" << endl;
		incSP();
	}
}

/**   Writes the assembly code that is the translation of the given command (either C_PUSH or C_POP)  */
void writePushPop(CodeWriter::command_t command, string segment, int index)
{
	// TODO
}


/* -------------------------------------------------------------------------------------------
 *	Assembly-translation helper methods
 *		Each of the below functions writes an often-used piece of VM-logic to the output in assembly code.
 * ------------------------------------------------------------------------------------------- */

/**
*	Writes the assembly code for popping the stack to the D register.
*/
void CodeWriter::popD()
{
	output << "@SP" << endl;
	output << "AM = M-1" << endl;
	output << "D = M" << endl;
}

/**
*	Writes the assembly code for decrementing the stack pointer.
*/
void CodeWriter::decSP()
{
	output << "@SP" << endl;
	output << "AM = M-1" << endl;
}

/**
*	Writes the assembly code for incrementing the stack pointer.
*/
void CodeWriter::incSP()
{
	output << "@SP" << endl;
	output << "AM = M+1" << endl;
}





