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

    while ((pdir = readdir(dir))) 
    {
		string fileName = pdir->d_name;
    	if (fileName.size() > 3 && fileName.substr(fileName.size()-3, fileName.size()-1) == ".vm")
    	{
			string fullPath = path + "/" + fileName;
    		files.push_back(fullPath);
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
	
	string translatee = argv[1];	// file/directory to be translated
	
	// set up the output
	ofstream output;
	string outputName;
	if (translatee.substr(translatee.size()-3, translatee.size()-1) == ".vm")
	{
		outputName = translatee.substr(0, translatee.size()-3) + ".asm";
	}
	else
	{
		outputName = translatee + ".asm";
	}
	output.open(outputName.c_str());
	if (!output.is_open())
	{
		cerr << "Cannot open output file " << outputName << endl;
		return 1;
	}
	CodeWriter writer = CodeWriter(output);
	
	// translate .vm file or directory of .vm files
	if (translatee.substr(translatee.size()-3, translatee.size()-1) == ".vm")  // single .vm file
	{
		ifstream source;
		source.open(translatee);
		if (!source.is_open())
		{
			cerr << "Cannot open source file " << translatee << endl;
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
	else	// directory
	{
		vector<string> files;
		files = getVMFiles(translatee);
		
		for (vector<string>::iterator iter = files.begin(); iter != files.end(); iter++)
		{
			ifstream source;
			source.open(*iter);
			if (!source.is_open())
			{
				cerr << "Error: cannot open " << *iter << endl;
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
	}	
	output.close();
}
