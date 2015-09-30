/**
 *	File: CodeWriter.hpp
 *	
 *	Translates VM commands into Hack assembly code.
 *
 *	Author: matthew.james.bird@gmail.com
 */

#ifndef CODEWRITER_HPP
#define CODEWRITER_HPP

#include <iostream>
#include <fstream>

#include "VMT.hpp"

using namespace std;
using namespace vmt;

/**
 *	Class: Parser
 *	Translates VM commands into Hack assembly code.
 */
class CodeWriter
{
public:
	CodeWriter(ofstream&);
	~CodeWriter();
	
	/**
	 *	Informs the code writer that the translation of a new VM file has started.
	 */
	void setFileName(string);
	
	/**
	*	Writes the assembly code that is the translation of the given arithmetic command.
	*	Returns true if success, else false.
	*/
	void writeArithmetic(string);
		
	/**
	*	Writes the assembly code that is the translation of the given command (either C_PUSH or C_POP).
	*	Returns true if success, else false.
	*/
	void writePushPop(command_t command, string segment, int index, string fileName);
	
	/**
	*	Writes the comparison comp to the output, where comp is either EQ, GT, or LT.
	*/
	void writeCompare(string comp, int& labelCounter);

 	/**
	*	Writes assembly code that effects the VM initialisation (bootstrap code) place at the beginning of the output file.
	*/
	void writeInit();

	/**
	*	Writes the assembly code that effects the label command.
	*/
	void writeLabel(string label);

	/**
	*	Writes the assembly code that effects the goto command.
	*/
	void writeGoto(string label);

	/**
	*	Writes the assembly code that effects the if-goto command.
	*/
	void writeIf(string label);

	/**
	*	Writes the assembly code that effects the call command.
	*/
	void writeCall(string functionName, int numArgs);

	/**
	*	Writes the assembly code that effects the return command.
	*/
	void writeReturn();

	/**
	*	Writes the assembly code that effects the function command.
	*/
	void writeFunction(string functionName, int numLocals);
	
private:
	ofstream& output;
	string fileName;
	
   /* ----------------------------------------------------------------------------------------------------
    *	Assembly-translation helper methods and members
    *	Each of the below methods writes an often-used piece of VM-logic to the output in assembly code.
    * ---------------------------------------------------------------------------------------------------- */
	
	// label counters
	static int eqLabel;
	static int gtLabel;
	static int ltLabel;
	
   	/**
	*	Writes the assembly code for popping the stack to the D register.
	*/
	void popToD();
	
   	/**
	*	Writes the assembly code for decrementing the stack pointer.
	*/
	void decSP();
	
   	/**
	*	Writes the assembly code for incrementing the stack pointer.
	*/
	void incSP();
	
	/**
	*	Sets the top of the stack to s. Do not call with A or M.
	*/
	void setStack(string s);

	/**
	*	Push RAM[*seg + index] to stack.
	*/
	void pushSegment(string seg, int index);
	
	/**
	*	Push RAM[base + index] to stack.
	*/
	void pushFixedSegment(string base, int index);
	
	/**
	*	Pop stack to RAM[*seg + index].
	*/
	void popToSegment(string seg, int index);
	
	/**
	*	Pop stack to RAM[base + index].
	*/
	void popToFixedSegment(string base, int index);
   
};

#endif /* CODEWRITER_HPP */
