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
	output << "@0" << endl;
	output << "M = 256" << endl;
	// call Sys.init
}

/**
*	Writes the assembly code that effects the label command.
*/
void CodeWriter::writeLabel(string label)
{
	output << "(" << "label" << ")" << endl;
}

/**
*	Writes the assembly code that effects the goto command.
*/
void CodeWriter::writeGoto(string label)
{
	output << "@" << label << endl;
	output << "0;JMP" << endl;
}

/**
*	Writes the assembly code that effects the if-goto command.
*/
void CodeWriter::writeIf(string label)
{
	popToD();
	output << "@" << label << endl;
	output << "D;JNE" << endl;
}

/**
*	Writes the assembly code that effects the call command.
*/
void CodeWriter::writeCall(string functionName, int numArgs)
{
	//TODO
	// use case: call xxx
	// save caller's frame onto stack
	// (for return) push the address of the next command onto the stack (for return address)
	// allocate space for local variables of the called subroutine (xxx)
	// jump to execute code (@functionName, 0;JMP)
}

/**
*	Writes the assembly code that effects the return command.
*/
void CodeWriter::writeReturn()
{
	//TODO
	// (requires) when we encountered call xxx we push the address of the next command to the stack (the return address)
	// pop the return address from the stack and goto it
	// return value???
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
// TODO: shouldn't the filename arg just be the m_filename?
void CodeWriter::writePushPop(command_t command, string segment, int index)
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
 *	Assembly-translation helper methods.
 *	Each of the below methods writes an often-used piece of VM-logic to the output in assembly code.
 *	(Overwrites ?) means that the function overwrites the values currently stored in the ? register.
 * --------------------------------------------------------------------------------------------------- */

/**
 *	Writes the assembly code for popping the stack to the D register.
 *	(Overwrites A and D)
 */
void CodeWriter::popToD()
{
	output << "@SP" << endl;
	output << "AM = M-1" << endl;
	output << "D = M" << endl;
}

/**
 *	Writes the assembly code for decrementing the stack pointer.
 *	(Overwrites A)
 */
void CodeWriter::decSP()
{
	output << "@SP" 	<< endl;
	output << "AM = M-1" << endl;
}

/**
 *	Writes the assembly code for incrementing the stack pointer.
 *	(Overwrites A)
 */
void CodeWriter::incSP()
{
	output << "@SP" 	<< endl;
	output << "AM = M+1" << endl;
}

/**
 *	Sets the top of the stack to n. Do not call with A or M.
 *	(Overwrites A)
 */
void CodeWriter::setStack(string s) 
{
	output << "@SP"			<< endl;
	output << "AM = M"		<< endl;
	output << "M = " << s 	<< endl;
}

/**
 *	Push RAM[*seg + index] to stack.
 *	(Overwrites A and D)
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
 *	(Overwrites A and D)
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
 *	(Overwrites A, D and RAM[13])
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
 *	(Overwrites A, D and RAM[13])
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
 *	(Overwrites A and D)
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
