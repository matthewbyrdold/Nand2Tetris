/**
 *	File: CodeWriter.cpp
 *	
 *	Translates VM commands into Hack assembly code.
 *
 *	Author: matthew.james.bird@gmail.com
 */


#include <iostream>
#include <fstream>

#include "CodeWriter.hpp"

using namespace std;
using namespace vmt;

const string pointerBase = "3";
const string tempBase = "5";

int CodeWriter::eqLabel = 0;
int CodeWriter::gtLabel = 0;
int CodeWriter::ltLabel = 0;


CodeWriter::CodeWriter(ofstream& file)
	: output(file)
{}
	
CodeWriter::~CodeWriter()
{
	output.close();
}
	
/**    
 *	Informs the code writer that the translation of a new VM file has started.  
 */
void CodeWriter::setFileName(string file)
{
	fileName = file;
}

/**
*	Writes the assembly code that effects the VM initialisation (bootstrap code) place at the beginning of the output file.
*/
void CodeWriter::writeInit()
{
	// TODO
}

/**
*	Writes the assembly code that effects the label command.
*/
void CodeWriter::writeLabel()
{
	//TODO
}

/**
*	Writes the assembly code that effects the goto command.
*/
void CodeWriter::writeGoto()
{
	//TODO
}

/**
*	Writes the assembly code that effects the if-goto command.
*/
void CodeWriter::writeIf(string label)
{
	//TODO
}

/**
*	Writes the assembly code that effects the call command.
*/
void CodeWriter::writeCall(string functionName, int numArgs)
{
	//TODO
}

/**
*	Writes the assembly code that effects the return command.
*/
void CodeWriter::writeReturn()
{
	//TODO
}

/**
*	Writes the assembly code that effects the function command.
*/
void CodeWriter::writeFunction(string functionName, int numLocals)
{
	//TODO
}

/**   
 *	Writes the assembly code that is the translation of the given arithmetic command.  
 */
void CodeWriter::writeArithmetic(string command)
{	
	if (command == "add")
	{
		popToD();
		decSP();
		output << "M = D+M" << endl;
		incSP();
	}
	else if (command == "sub")
	{
		popToD();
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
		writeCompare("EQ", eqLabel);
	}
	else if (command == "gt")
	{
		writeCompare("GT", gtLabel);
	}
	else if (command == "lt")
	{
		writeCompare("LT", ltLabel);
	}
	else if (command == "and")
	{
		popToD();
		decSP();
		output << "M = D&M" << endl;
		incSP();
	}
	else if (command == "or")
	{
		popToD();
		decSP();
		output << "M = D|M" << endl;
		incSP();
	}
	else if (command == "not")
	{
		popToD();
		output << "M = !D" << endl;
		incSP();
	}
}

/**
 *	Writes the assembly code that is the translation of the given command (either C_PUSH or C_POP)  
 */
void CodeWriter::writePushPop(command_t command, string segment, int index, string fileName)
{
	if (command == C_PUSH)
	{
		if (segment == "constant")
		{
			output << "@" << index 	<< endl;
			output << "D = A" 	<< endl;
			setStack("D");
			incSP();
		}
		else if (segment == "local")
		{
			pushSegment("LCL", index);
		}
		else if (segment == "argument")
		{
			pushSegment("ARG", index);
		}
		else if (segment == "this")
		{
			pushSegment("THIS", index);
		}
		else if (segment == "that")
		{
			pushSegment("THAT", index);
		}
		else if (segment == "pointer")
		{
			pushFixedSegment(pointerBase, index);
		}
		else if (segment == "temp")
		{
			pushFixedSegment(tempBase, index);
		}
		else if (segment == "static")
		{
			output << "@" << fileName << "." << index << endl;
			output << "D = M" << endl;
			setStack("D");
			incSP();
		}
	}
	else if (command == C_POP)
	{
		if (segment == "local")
		{
			popToSegment("LCL", index);
		}
		else if (segment == "argument")
		{
			popToSegment("ARG", index);
		}
		else if (segment == "this")
		{
			popToSegment("THIS", index);
		}
		else if (segment == "that")
		{
			popToSegment("THAT", index);
		}
		else if (segment == "pointer")
		{
			popToFixedSegment(pointerBase, index);
		}
		else if (segment == "temp")
		{
			popToFixedSegment(tempBase, index);
		}
		else if (segment == "static")
		{
			popToD();
			output << "@" << fileName << "." << index << endl;
			output << "M = D" << endl;
		}
	}
}


/* ---------------------------------------------------------------------------------------------------
 *	Assembly-translation helper methods
 *	Each of the below methods writes an often-used piece of VM-logic to the output in assembly code.
 * --------------------------------------------------------------------------------------------------- */

/**
 *	Writes the assembly code for popping the stack to the D register.
 */
void CodeWriter::popToD()
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
	output << "@SP" 	<< endl;
	output << "AM = M-1" << endl;
}

/**
 *	Writes the assembly code for incrementing the stack pointer.
 */
void CodeWriter::incSP()
{
	output << "@SP" 	<< endl;
	output << "AM = M+1" << endl;
}

/**
 *	Sets the top of the stack to n. Do not call with A or M.
 */
void CodeWriter::setStack(string s) 
{
	output << "@SP"			<< endl;
	output << "AM = M"		<< endl;
	output << "M = " << s 	<< endl;
}

/**
 *	Push RAM[*seg + index] to stack.
 */
void CodeWriter::pushSegment(string seg, int index)
{
	output << "@" << seg	<< endl;
	output << "D = M" 		<< endl;
	output << "@" << index  << endl;
	output << "A = D+A"		<< endl;
	output << "D = M"		<< endl;
	setStack("D");
	incSP();
}

/**
 *	Push RAM[base + index] to stack.
 */
void CodeWriter::pushFixedSegment(string base, int index)
{
	output << "@" << base		 << endl;
	output << "D = A" 			 << endl;
	output << "@" << index		<< endl;
	output << "A = A+D"			<< endl;
	output << "D = M"			<< endl;
	setStack("D");
	incSP();
}

/**
 *	Pop stack to RAM[*seg + index].
 */
void CodeWriter::popToSegment(string seg, int index)
{
	output << "@" << seg	<< endl;
	output << "D = M" 		<< endl;
	output << "@" << index  << endl;
	output << "D = D+A"		<< endl;
	output << "@R13"		<< endl;
	output << "M = D"		<< endl;
	popToD();
	output << "@R13"		<< endl;
	output << "A = M"		<< endl;
	output << "M = D"		<< endl;
}

/**
 *	Pop stack to RAM[base + index].
 */
void CodeWriter::popToFixedSegment(string base, int index)
{
	output << "@" << base		<< endl;
	output << "D = A" 			<< endl;
	output << "@" << index 		<< endl;
	output << "D = A+D"			<< endl;
	output << "@R13"			<< endl;
	output << "M = D"			<< endl;
	popToD();
	output << "@R13"			<< endl;
	output << "A = M"			<< endl;
	output << "M = D"			<< endl;
}

/**
 *	Writes the comparison comp to the output, where comp is either EQ, GT, or LT.
 */
void CodeWriter::writeCompare(string comp, int& labelCounter)
{
	popToD();
	decSP();
	output << "D = M-D" << endl;
	output << "@" << comp << "_" << labelCounter << endl;
	output << "D;J" << comp << endl;
	setStack("0");
	output << "@" << comp << "_FIN_" << labelCounter << endl;
	output << "0;JMP" << endl;
	output << "(" << comp << "_" << labelCounter << ")" << endl;
	setStack("-1");
	output << "(" << comp << "_FIN_" << labelCounter << ")" << endl;
	incSP();
	
	++labelCounter;	
}
