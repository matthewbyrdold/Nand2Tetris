/**
 *	file: VMcodewriter.cpp
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
	filename = file;
}

/**   Writes the assembly code that is the translation of the given arithmetic command.  */
void CodeWriter::writeArithmetic(string)
{
	//TODO
}

/**   Writes the assembly code that is the translation of the given command (either C_PUSH or C_POP)  */
void writePushPop(CodeWriter::command_t command, string segment, int index)
{
	// TODO
}
