/**   JackCompiler.cpp
 *    The main calling routine for the Jack Compiler
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

int main(int argc, char* argv[])
{
    cout << "The Jack Compiler" << endl; 

    // check usage
    if (argc != 2)
    {
        cerr << "Usage: ./ source" << endl;
        return 1;
    }

    Analyser analyser;
    Tokeniser tokeniser;
    CompilationEngine engine;    
    
    string compileTarget = argv[1];

    auto filesToCompile = getFiles(compileTarget);
    if (filesToCompile.size() == 0)
    {
        cerr << "ERROR: no jack files found @ " << argv[1] << endl;
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
            cerr << "ERROR: problem opening output file for " 
                 << fileToCompile << endl;
            return 1;
        }

        // translate file
    }
}

