/**   Analyser.cpp
 *    Top-level driver that sets up and invokes the other modules.
 *    matthew.james.bird@gmail.com
 */

#include <Analyser.h>

#include <CompilationEngine.h>
#include <Tokeniser.h>
#include <FileHelpers.h>

#include <iostream>
#include <fstream>
#include <vector>

using std::cout; 
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;

Analyser::Analyser()
{
}

Analyser::~Analyser()
{
}

int Analyser::compile(std::string compileTarget)
{
    auto filesToCompile = getFiles(compileTarget);
    if (filesToCompile.size() == 0)
    {
        cerr << "ERROR: no jack files found @ " << compileTarget << endl;
        return 1;
    }
    
    for (auto fileToCompile : filesToCompile)
    {
        ofstream input = openFileToCompile(fileToCompile);
        if (!input.is_open())
        {
            cerr << "ERROR: problem opening input file " 
                 << fileToCompile << endl;
            return 1;
        }

        ofstream output = openOutputFileFor(fileToCompile);
        if (!output.is_open())
        {
            cerr << "ERROR: problem creating output file for " 
                 << fileToCompile << endl;
            return 1;
        }

        // compile
        Tokeniser tokeniser(input);
    }

    return 0;
}
