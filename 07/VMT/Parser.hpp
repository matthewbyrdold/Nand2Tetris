/**
 *	File: VMparser.hpp
 *	
 *	Handles the parsing of a single .vm file, and encapsulates access to the input code. 
 *	It reads VM commands, parses them, and provides convenient access to their components. 
 *	In addition, it removes all white space and comments.
 *
 *	Author: matthew.james.bird@gmail.com
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VMT.hpp"

using namespace std;
using namespace vmt;

/**
 *	Class: Parser
 *	Handles the parsing of a single .vm file, and encapsulates access to the input code. 
 *	It reads VM commands, parses them, and provides convenient access to their components. 
 *	In addition, it removes all white space and comments.
 */
class Parser
{
public:
	Parser(ifstream& sourceFile, string fileName);

	/**
	 * 	Returns whether there are more commands in source. 
	 */
	bool hasMoreCommands();
	
	/** 
	 *	Reads the next command from input.
	 *	Should not be called if hasMoreCommands() is false. 
	 * 	Returns false if command empty, else true.
	 */
	bool advance();
		
	/**
	 *	Returns the type of the current command. 
	 */
	command_t commandType();
	
	/** 
	 *	Returns the first argument of the current command.
	 *	In the case of C_ARITHMETIC, the command itself (add, sub, etc.) is returned.
	 *	Should not be called in the current command is C_RETURN.
	 */
	string arg1();	
	
	/** 
	 *	Returns the second argument of the current command.
	 *	Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL. 
	 */
	string arg2();
	
	/** Returns the name of the source file */
	string& getFileName();
		
private:
	/** Returns the nth argument of the current command. */
	string nth_argument(int);
		
	ifstream& source;
	string command;
	string fileName;
};

#endif /* PARSER_HPP */
