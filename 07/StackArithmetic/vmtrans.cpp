/**
 *	file: vmtrans.cpp
 *
 */

#include <iostream>
#include <fstream>
#include <string>

#include "vmtrans.hpp"

using namespace std;

Parser::Parser(ifstream& file)
	: source(file)
{}
	
/** Returns whether there are more commands in source. */
bool Parser::hasMoreCommands()
{
	return (source.peek() != EOF);
}

/** Reads the next command from input.
	Should not be called if hasMoreCommands() is false. */
void advance()
{
	// TODO
}

enum command_t {C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL};

/** Returns the type of the current command. */
command_t CommandType()
{
	// TODO
	return C_ARITHMETIC;
}

/** Returns the first argument of the current command.
	In the case of C_ARITHMETIC, the command itself (add, sub, etc.) is returned.
	Should not be called in the current command is C_RETURN */
string arg1()
{
	// TODO
	return "test";
}

/** Returns the second argument of the current command.
	Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL. */
string arg2()
{
	// TODO
	return "test2";
}



