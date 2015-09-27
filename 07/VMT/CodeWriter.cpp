/**
 *	File: CodeWriter.cpp
 *	
 *	Translates VM commands into Hack assembly code.
 *
 *	Author: matthew.james.bird@gmail.com
 */


#include <iostream>
#include <fstream>

#include "VMT.hpp"
#include "CodeWriter.hpp"

using namespace std;
using namespace vmt;

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
	
/**	  Informs the code writer that the translation of a new VM file has started.  */
void CodeWriter::setFileName(string file)
{
	fileName = file;
}

/**   Writes the assembly code that is the translation of the given arithmetic command.  */
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
		popToD();
		decSP();
		output << "D = M-D" 					<< endl;
		output << "@EQ_" << eqLabel 			<< endl;
		output << "D;JEQ" 						<< endl;
		setStack("0");
		output << "@EQ_FIN_" << eqLabel			<< endl;
		output << "0;JMP"						<< endl;
		output << "(EQ_" << eqLabel << ")" << endl;
		setStack("-1");
		output << "(EQ_FIN_" << eqLabel << ")" 	<< endl;
		incSP();
		
		++eqLabel;
	}
	else if (command == "gt")
	{
		popToD();
		decSP();
		output << "D = M-D" 					<< endl;
		output << "@GT_" << gtLabel 			<< endl;
		output << "D;JGT" 						<< endl;
		setStack("0");
		output << "@GT_FIN_" << gtLabel			<< endl;
		output << "0;JMP"						<< endl;
		output << "(GT_" << gtLabel << ")"		<< endl;
		setStack("-1");
		output << "(GT_FIN_" << gtLabel << ")" 	<< endl;
		incSP();
		++gtLabel;
	}
	else if (command == "lt")
	{
		popToD();
		decSP();
		output << "D = M-D" 					<< endl;
		output << "@LT_" << ltLabel 			<< endl;
		output << "D;JLT" 						<< endl;
		setStack("0");
		output << "@LT_FIN_" << ltLabel			<< endl;
		output << "0;JMP"						<< endl;
		output << "(LT_" << ltLabel << ")"		<< endl;
		setStack("-1");
		output << "(LT_FIN_" << ltLabel << ")" 	<< endl;
		incSP();
		++ltLabel;
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

/**   Writes the assembly code that is the translation of the given command (either C_PUSH or C_POP)  */
void CodeWriter::writePushPop(vmt::command_t command, string segment, int index)
{
	// TODO
	if (command == C_PUSH)
	{
		if (segment == "constant")
		{
			output << "@" << index 	<< endl;
			output << "D = A" 		<< endl;
			setStack("D");
			incSP();
		}
		else if (segment == "local")
		{
			// push local[index] to stack
			output << "@LCL" 		<< endl;
			output << "D = A" 		<< endl;
			output << "@" << index  << endl;
			output << "A = D+A"		<< endl;
			output << "D = M"		<< endl;
			setStack("D");
			incSP();
		}
	}
	else if (command == C_POP)
	{
		if (segment == "local")
		{
			// pop stack to local[index]	
			output << "@LCL" 		<< endl;
			output << "D = A" 		<< endl;
			output << "@" << index  << endl;
			output << "D = D+A"		<< endl;
			output << "@R13"		<< endl;
			output << "M = D"		<< endl;
			popToD();
			output << "@R13"		<< endl;
			output << "A = M"		<< endl;
			output << "M = D"		<< endl;
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

/**
*	Sets the top of the stack to n. 
*/
void CodeWriter::setStack(string s) {
	output << "@SP"		  << endl;
	output << "AM = M"	  << endl;
	output << "M = " << s << endl;
}



