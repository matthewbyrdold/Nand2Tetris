/**
 *	file: VMcodewriter.hpp
 *
 */

#include <iostream>
#include <fstream>

using namespace std;

class CodeWriter
{
public:
	CodeWriter(ofstream&);
	~CodeWriter();
	
	/**
	 *	Informs the code writer that the translation of a new VM file has started.
	 */
	void setFileName(string);
	
   /**
    *	Writes the assembly code that is the translation of the given arithmetic command.
    */
	void writeArithmetic(string);
	
	enum command_t {C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL};
	
   /**
    *	Writes the assembly code that is the translation of the given command (either C_PUSH or C_POP)
    */
	void writePushPop(command_t, string, int);
	
	
private:
	ofstream& output;
	string filename;
};


/**
 *	
 *
 */