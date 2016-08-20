/**
 *  File: VMtranslator.cpp
 *  Author: matthew.james.bird@gmail.com
 *
 *  Translates a single .vm file or a folder of .vm files into HACK assembly code.
 *  
 *  Usage: ./VMtranslator source
 *      where source is either a file of the form 'xxx.vm', or a directory of such files.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>

#include "Parser.hpp"
#include "CodeWriter.hpp"
#include "VMT.hpp"
#include "mediator.hpp"

using namespace std;
using namespace vmt;


int main(int argc, char* argv[])
{
    // check usage
    if (argc != 2)
    {
        cerr << "Usage: ./VMtranslator source" << endl;
        return 1;
    }
    
    string translatee = argv[1];    // file/directory to be translated
    
    // set up the output
    string outputName;  
    if (isVMFile(translatee))
    {
        outputName = translatee.substr(0, translatee.size()-3) + ".asm";
    }
    else // directory
    {
        if (translatee == ".")
        {
            outputName = lastPartOfPath(currentDirectory()) + ".asm";
        }
        else
        {
            outputName = translatee + "/" + lastPartOfPath(translatee) + ".asm";
        }
    }
    std::cout << "Creating assembly file " << outputName << std::endl;
    
    ofstream output;
    output.open(outputName.c_str());
    if (!output.is_open())
    {
        cerr << "Cannot open output file " << outputName << endl;
        return 1;
    }
    
    CodeWriter writer = CodeWriter(output);
    
    // translate .vm file or directory of .vm files
    if (isVMFile(translatee))
    {
        ifstream source;
        source.open(translatee);
        if (!source.is_open())
        {
            cerr << "Cannot open source file " << translatee << endl;
            return 1;
        }
        
        // remove the .vm bit of the translatee file name
        int lastIndex = translatee.find_last_of("."); 
        string rawName = translatee.substr(0, lastIndex); 
        
        Parser parser = Parser(source, rawName);

        translate(parser, writer);
        
        source.close();
    }
    else    // directory
    {
        vector<string> files;
        files = getVMFiles(translatee);
        // go through the files in the directory, translating each
        for (vector<string>::iterator iter = files.begin(); iter != files.end(); iter++)
        {
            cout << "Translating " << *iter << endl;
            ifstream source;
            source.open(*iter);
            if (!source.is_open())
            {
                cerr << "Error: cannot open " << *iter << endl;
                return 1;
            }
            
            // Remove the .vm bit of the translatee file name
            // As a consequence of the stripping of the full path,
            // we cannot have two classes with the same name, even
            // in different directories. This is something to consider
            // changing...
            int lastIndex = iter->find_last_of("."); 
            string rawName = iter->substr(0, lastIndex); 
            rawName = lastPartOfPath(rawName);
            Parser parser = Parser(source, rawName);
            
            translate(parser, writer);
            
            source.close();
        }
    }   
    std::cout << "Translation complete" << std::endl; // TODO: would be nice to see whether successful or not?
    output.close();
}
