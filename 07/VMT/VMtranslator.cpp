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

/**
 * getVMFiles: Returns a list of all .vm files in path.
 */
vector<string> getVMFiles(string path = ".") {
    DIR* dir;
    dirent* pdir;
    vector<string> files;

    dir = opendir(path.c_str());

    while (pdir = readdir(dir)) 
    {
    	if (pdir->d_name.substr(pdir->d_name.size()-3, pdir->d_name.size()-1) == ".vm")
    	{
    		files.push_back(pdir->d_name);
    	}
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
	
	// set up the output
	ofstream output;
	string outputName;
	if (argv[1].substr(argv[1].size()-3, arg[1].size()-1) == ".vm")
	{
		outputName = argv[1].substr(0, argv[1].size()-3) + ".asm";
	}
	else
	{
		outputName = argv[1] + ".asm";
	}
	output.open(outputName.c_str());
	if (!output.is_open())
	{
		cerr << "Cannot open output file " << outputName << endl;
		return 1;
	}
	CodeWriter writer = CodeWriter(output);
	
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
			
		// Parse the file
		Parser parser = Parser(source);

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
	}
	else         // directory
	{
		vector<string> files;
		files = getVMFiles(argv[1]);
		
		while (int i = 0; !files.empty(); ++i)
		{
			fstream source;
			source.open(files[i]);
			if (!source.is_open())
			{
				cerr << "Error: cannot open " << files[i] << endl;
	    		return 1;
			}
			
			// Parse the file
			Parser parser = Parser(source);
			
			/////////// DO THE PARSING
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
		}
	}	
	output.close();
}
