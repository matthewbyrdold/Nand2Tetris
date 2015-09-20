/**
 *	file: CodeWriter.cpp
 *
 */

#include <iostream>
#include <fstream>

#include "CodeWriter.hpp"

using namespace std;

int CodeWriter::eqLabel = 0;

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
	else if (command == "neg")
	{
		decSP();
		output << "M = -M" << endl;
		incSP();
	}
	else if (command == "eq")
	{
		popD();
		decSP();
		output << "D = M-D" 					<< endl;
		output << "@EQ_ZERO_" << eqLabel 		<< endl;
		output << "D;JEQ" 						<< endl;
		output << "M = 0"						<< endl;
		incSP();
		output << "@EQ_FIN_" << eqLabel			<< endl;
		output << "0;JMP"						<< endl;
		output << "(EQ_ZERO_" << eqLabel << ")" << endl;
		output << "M = -1"						<< endl;
		incSP();
		output << "(EQ_FIN_" << eqLabel << ")" 	<< endl;
		eqLabel++;
	}
	else if (command == "gt")
	{
		
	}
	else if (command == "lt")
	{
		
	}
	else if (command == "and")
	{
		
	}
	else if (command == "or")
	{
		
	}
	else if (command == "not")
	{
		
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





