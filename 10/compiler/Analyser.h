/**   Analyser.h
 *    Top-level syntax analyser that sets up and invokes a tokenizer and compilation engine.
 *    matthew.james.bird@gmail.com
 */

#ifndef analyser_h
#define analyser_h

#include <iostream>

/** 
 *  Operates on a given source, where source is either a file name of the form
 *  xxx.Jack or a directory containing one or many such files. For each source
 *  xxx.Jack file, the analyser creates a Tokeniser and feeds in the file, 
 *  creates an output file called xxx.xml, and uses the CompilationEngine to 
 *  compile the Tokeniser output into the output file.
 */
class Analyser {
public:
    Analyser();
    ~Analyser();

    int compile(std::string);
};

#endif // analyser_h    
