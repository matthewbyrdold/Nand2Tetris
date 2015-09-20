/**
 *	file: VMtranslator.cpp
 *	author: matthew.james.bird@gmail.com
 *
 *	Translates a single .vm file or a folder of .vm files into HACK assembly code.
 *	
 *	Usage: ./VMtranslator source
 *		where source is either a file of the form 'xxx.vm', or a directory of such files.
 */

#include <iostream>
#include <fstream>
#include <string>

#include "vmtrans.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: ./VMtranslator source" << endl;
		return 1;
	}
	
	// TODO: DIRECTORY INPUT!
	// if argv[1][end] != .vm, then go through named directory file by file, doing a different parser for each
	
	ifstream source;
	source.open(argv[1]);
	if (!source.is_open())
	{
		cerr << "Cannot open source file " << argv[1] << endl;
		return 1;
	}
	
	// Parse the file
	Parser parser = Parser(source);
	
	// tests
	while (parser.hasMoreCommands())
	{
		parser.advance();
	}
	
	source.close();
}
