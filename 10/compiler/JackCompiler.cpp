/**   JackCompiler.cpp
 *    Simple main function which calls the analyser on the CLI-provided
 *    file/directory to compile and kicks off compilation.
 *    matthew.james.bird@gmail.com
 */

#include <Analyser.h>

#include <iostream>

using std::cout; 
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
    // check usage
    if (argc != 2)
    {
        cerr << "Usage: ./ source" << endl;
        return 1;
    }
    string compileTarget = argv[1];

    Analyser analyser;
    int status = analyser.compile(compileTarget);
    if (status == 0)
    {
        cout << "Compilation success" << endl;
    }
    else
    {
        cout << "Compilation failure" << endl;
    }
}

