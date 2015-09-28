/**
 *	File: VMtranslator.cpp
 *	Author: matthew.james.bird@gmail.com
 *
 *	Translates a single .vm file or a folder of .vm files into HACK assembly code.
 *	
 *	Usage: ./VMtranslator source
 *		where source is either a file of the form 'xxx.vm', or a directory of such files.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>

#include "Parser.hpp"
#include "CodeWriter.hpp"
#include "VMT.hpp"

using namespace std;
using namespace vmt;

vector<string> getFiles(string path = ".") {
    DIR* dir;
    dirent* pdir;
    vector<string> files;

    dir = opendir(path.c_str());

    while (pdir = readdir(dir)) {
        files.push_back(pdir->d_name);
    }
    
    return files;
}


int main(int argc, char* argv[])
{
	
	if (argc != 2)
	{
		cerr << "Usage: ./VMtranslator source" << endl;
		return 1;
	}
	
	////////////////////////////////////////
	if (argv[1].substr(argv[1].size()-3, arg[1].size()-1) == ".vm")  // single .vm file
	{
		ifstream source;
		source.open(argv[1]);
		if (!source.is_open())
		{
			cerr << "Cannot open source file " << argv[1] << endl;
			return 1;
		}
		
		ofstream output;
		output.open("test.asm");
		if (!output.is_open())
		{
			cerr << "Cannot open source file test.asm" << endl;
			return 1;
		}
			
		// Parse the file
		Parser parser = Parser(source);
		CodeWriter writer = CodeWriter(output);
		
		// TEST CODE
		while (parser.hasMoreCommands())
		{
			if (parser.advance() == false)
			{
				continue;
			}
			if (parser.commandType() == C_PUSH)
			{
				int i = atoi(parser.arg2().c_str());
				writer.writePushPop(C_PUSH, parser.arg1(), i);
			}
			else if (parser.commandType() == C_POP)
			{
				int i = atoi(parser.arg2().c_str());
				writer.writePushPop(C_POP, parser.arg1(), i);
			}
			else if (parser.commandType() == C_ARITHMETIC)
			{
				writer.writeArithmetic(parser.arg1());
			}
		}
		
		source.close();
		output.close();
	}
	else         // directory
	{
		while (STUFF IN VECTOR)
		{
			vector<string> f;
			
			f = getFiles(argv[1]); // or pass which dir to open
			
			fstream file;
			
			file.open(f[0]);
			if (!file.is_open())
			{
				cerr << "Error: cannot open " << f[n] << endl;
	    			return 1;
			}
	
			 return 0;
		}
	}	
}
