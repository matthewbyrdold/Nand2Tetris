/**   Analyser.h
 *    Top-level driver that sets up and invokes the other modules.
 *    matthew.james.bird@gmail.com
 */

#ifndef analyser_h
#define analyser_h

/** 
 *  Operates on a given source, where source is either a file name of the form
 *  xxx.Jack or a directory containing one or many such files. For each source
 *  xxx.Jack file, the analyser creates a Tokeniser and feeds in the file, 
 *  creates an output file called xxx.xml, and uses the CompilationEngine to 
 *  compile the Tokeniser output into the output file.
 */
class Analyser {
public:

};

#endif // analyser_h    
