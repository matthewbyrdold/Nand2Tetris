/**
 *	file: CodeWriter.hpp
 *
 */

#include <iostream>
#include <fstream>

using namespace std;

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
	
	enum command_t {C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL};
	
   /**
    *	Writes the assembly code that is the translation of the given command (either C_PUSH or C_POP)
	*	Returns true if success, else false.
    */
	void writePushPop(command_t, string, int);
	
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
};





