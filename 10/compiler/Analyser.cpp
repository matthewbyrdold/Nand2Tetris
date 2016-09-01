/**   Analyser.cpp
 *    Top-level driver that sets up and invokes the other modules.
 *    matthew.james.bird@gmail.com
 */

#include "Analyser.h"

#include "JackStatus.h"
#include "CompilationEngine.h"
#include "Tokeniser.h"
#include "FileHelpers.h"

#include <iostream>
#include <fstream>
#include <vector>

using std::cout; 
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

Analyser::Analyser()
{
}

Analyser::~Analyser()
{
}

JackStatus Analyser::compile(std::string compileTarget)
{
    auto filesToCompile = getFiles(compileTarget);
    if (filesToCompile.size() == 0)
    {
        cerr << "ERROR: no jack files found @ " << compileTarget << endl;
        return FileAccessFailure;
    }

    JackStatus status; 
    for (auto fileToCompile : filesToCompile)
    {
        ifstream input = openFileToCompile(fileToCompile);
        if (!input.is_open())
        {
            cerr << "ERROR: problem opening input file " 
                 << fileToCompile << endl;
            return FileAccessFailure;
        }

        ofstream output = openOutputFileFor(fileToCompile);
        if (!output.is_open())
        {
            cerr << "ERROR: problem creating output file for " 
                 << fileToCompile << endl;
            return FileAccessFailure;
        }

        std::cout << "Compiling " << fileToCompile << endl;

        // compile
        Tokeniser tokeniser(input, fileToCompile);
        CompilationEngine compiler(tokeniser, output);
        status = compiler.compileClass();
        if (status != Success)
        {
            std::cout << "Failed to compile " << fileToCompile << "\n" << endl;
            return status;
        }
        else
        {
            std::cout << "Successfully compiled " << fileToCompile << "\n" << endl;
        }
    }   
    return Success;
}
