/**
 *  File: mediator.cpp
 *  Author: matthew.james.bird@gmail.com
 *
 *  Functions for the mediator between the Parser and CodeWriter modules of the VM translator.
 *  
 */

#include "mediator.hpp"

#include <unistd.h> // for getting current dir on UNIX

/**
 *  isVMFile: Returns whether input is a single .vm file (false if input is a directory of .vm files).
 */
bool isVMFile(const string& input)
{
    if (input.size() < 3)
    {
        return false;
    }
    return input.substr(input.size()-3, input.size()-1) == ".vm";
}

/**
 *  lastPartOfPath: Returns the lowest level directory in a path.
 */
string lastPartOfPath(const string& path)
{
    size_t found;
    found = path.find_last_of("/\\");
    return path.substr(found + 1);
}

/**
 *  currentDirectory: Returns the name of the current directory on UNIX
 */
string currentDirectory()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        //fprintf(stdout, "Current working dir: %s\n", cwd);
        return cwd;
    }
    else
    {
        return ".";
    }
}
    
/**
 *  getVMFiles: Returns a list of all .vm files in path.
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
 *  translate: translates source into output.
 *  
 *  Returns whether there are any errors.
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
            case C_LABEL:
            {
                writer.writeLabel(parser.arg1());
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
            case C_FUNCTION:
            {
                int numArgs = atoi(parser.arg2().c_str());
                writer.writeFunction(parser.arg1(), numArgs);
                break;
            }
            case C_RETURN:
            {
                writer.writeReturn();
                break;
            }
            case C_CALL:
            {
                int numArgs = atoi(parser.arg2().c_str());
                writer.writeCall(parser.arg1(), numArgs);
                break;
            }
            default:
            {
                std::cerr << __FUNCTION__ << ": unrecognised command " 
                          << parser.commandType() << std::endl;
            }
        }
    }   
    return true;
}
