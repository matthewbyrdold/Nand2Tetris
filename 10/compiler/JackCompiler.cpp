/**   JackCompiler.cpp
 *    The main calling routine for the Jack Compiler
 *    matthew.james.bird@gmail.com
 */

#include <Analyser.h>
#include <CompilationEngine.h>
#include <Tokeniser.h>

#include <iostream>
#include <fstream>
#include <vector>

using std::cout; 
using std::cerr;
using std::endl;
using std::string;
using std::vector;

namespace {
    const vector<const string> getFiles(const string&);
}

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
    
    string compilee = argv[1];

    auto filesToCompile = getFiles(compilee);
    for (auto file : filesToCompile)
    {
        // make output file
        // translate file
    }
}


namespace { /** Helper functions */

    const vector<const string> getFiles(const string&)
    {
        const vector<const string> files;
        return files;
    }

} // namespace anonymous
