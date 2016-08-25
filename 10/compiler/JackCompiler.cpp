/**   JackCompiler.cpp
 *    The main calling routine for the Jack Compiler
 *    Operates on a given source, where source is either a file name of the form
 *    xxx.Jack or a directory containing one or many such files. For each source
 *    xxx.Jack file, creates a Tokeniser and feeds in the file, creates an output
 *    file called xxx.xml, and uses the CompilationEngine to compile the Tokeniser
 *    output into the output file.
 *    
 *    matthew.james.bird@gmail.com
 */

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
            cerr << "ERROR: problem creating output file for " 
                 << fileToCompile << endl;
            return 1;
        }

        // compile
    }
}

