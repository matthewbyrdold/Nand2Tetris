/**
 *	File: mediator.cpp
 *	Author: matthew.james.bird@gmail.com
 *
 *	Functions for the mediator between the Parser and CodeWriter modules of the VM translator.
 *	
 */

#include "mediator.hpp"

/**
 *	isVMFile: Returns whether input is a single .vm file (false if input is a directory of .vm files).
 */
bool isVMFile(const string& input)
{
	return input.substr(input.size()-3, input.size()-1) == ".vm";
}
	
/**
 *	getVMFiles: Returns a list of all .vm files in path.
 */
vector<string> getVMFiles(string path = ".") {
    DIR* dir;
    dirent* pdir;
    vector<string> files;

    dir = opendir(path.c_str());

    while ((pdir = readdir(dir))) 
    {
		string fileName = pdir->d_name;
    	if (isVMFile(fileName))
    	{
			string fullPath = path + "/" + fileName;
    		files.push_back(fullPath);
    	}
    }
    
    return files;
}

/**
 *	translate: translates source into output.
 *	
 *	Returns whether there are any errors.
 */
bool translate(Parser& parser, CodeWriter& writer)
{
    writer.setFileName(parser.getFileName());
	while (parser.hasMoreCommands())
	{
		if (!parser.advance())
		{
            // this command was empty
			continue;
		}
        switch(parser.commandType())
        {
            case C_PUSH:
            {
    			int index = atoi(parser.arg2().c_str());
    			writer.writePushPop(C_PUSH, parser.arg1(), index);
                break;
            }
            case C_POP:
            {
    			int index = atoi(parser.arg2().c_str());
    			writer.writePushPop(C_POP, parser.arg1(), index);
    		    break;
            }
    		case C_ARITHMETIC:
            {
    			writer.writeArithmetic(parser.arg1());
    		    break;
            }
            case C_GOTO:
            {
                writer.writeGoto(parser.arg1()); // is this the right num args?
                break;
            } 
            case C_IF:
            {
                writer.writeIf(parser.arg1());
                break;
            }
            default:
            {
                std::cerr << __FUNCTION__ << ": unrecognised command " 
                          << parser.commandType() << std::endl;
                // TODO: call, function, return, label, init?
            }
        }
	}	
	return true;
}
