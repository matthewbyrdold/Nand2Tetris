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

/** Reads the next command from input. */
void Parser::advance()
{
	string temp;
	char c;
	bool insertSpace = false;
	while ((source >> noskipws >> c) && (c != '\n') && (c != '/'))
	{
		if (isspace(c) && insertSpace)
		{
			temp += c;
			insertSpace = false;
		}
		else if (!isspace(c))
		{
			temp += c;
			insertSpace = true;
		}
	}
	
	// continue reading until newline or EOF
	while (c != '\n' && c != EOF && (source >> noskipws >> c));
	
	command = temp;
	if (command.size() > 1)// debug
	{
		cout << command << endl;	// debug
		//debugEND
	}//debugEND
}

/** Returns the type of the current command. */
Parser::command_t Parser::commandType()
{
	// TODO
	if (command.compare(0, 4, "push") == 0)
	{
		return C_PUSH;
	}
	else if (command.compare(0, 3, "pop") == 0)
	{
		return C_POP;
	}
	else if (command.compare(0, 5, "label") == 0)
	{
		return C_LABEL;
	}
	else if (command.compare(0, 4, "goto") == 0)
	{
		return C_GOTO;
	}
	else if (command.compare(0, 2, "if") == 0)
	{
		return C_IF;
	}
	else if (command.compare(0, 8, "function") == 0)
	{
		return C_FUNCTION;
	}
	else if (command.compare(0, 6, "return") == 0)
	{
		return C_RETURN;
	}
	else if (command.compare(0, 4, "call") == 0)
	{
		return C_CALL;		// TODO: is this the correct format for calls?
	}
	else 
	{
		return C_ARITHMETIC;
	}
}

/** Returns the first argument of the current command.
	In the case of C_ARITHMETIC, the command itself (add, sub, etc.) is returned.
	Should not be called in the current command is C_RETURN */
string Parser::arg1()
{
	// TODO
	return "test";
}

/** Returns the second argument of the current command.
	Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL. */
string Parser::arg2()
{
	// TODO
	return "test2";
}



