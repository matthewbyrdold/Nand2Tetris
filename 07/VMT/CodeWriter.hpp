/**
 *  File: CodeWriter.hpp
 *  
 *  Translates VM commands into Hack assembly code.
 *
 *  Author: matthew.james.bird@gmail.com
 */

#ifndef CODEWRITER_HPP
#define CODEWRITER_HPP

#include <iostream>
#include <fstream>

#include "VMT.hpp"

using namespace std;
using namespace vmt;

/**
 *  Class: Parser
 *  Translates VM commands into Hack assembly code.
 */
class CodeWriter
{
public:
    CodeWriter(ofstream&);
    ~CodeWriter();
    
    /**
     *  Informs the code writer that the translation of a new VM file has started.
     */
    void setFileName(string);
    
    /**
    *   Writes the assembly code that is the translation of the given arithmetic command.
    *   Returns true if success, else false.
    */
    void writeArithmetic(string);
        
    /**
    *   Writes the assembly code that is the translation of the given command 
    *   (either C_PUSH or C_POP).
    *   Returns true if success, else false.
    */
    void writePushPop(command_t command, string segment, int index);

    /**
    *   Writes assembly code that effects the VM initialisation (bootstrap code)
    *   place at the beginning of the output file.
    */
    void writeInit();

    /**
    *   Writes the assembly code that effects the label command.
    */
    void writeLabel(const string& label);

    /**
    *   Writes the assembly code that effects the goto command.
    */
    void writeGoto(const string& label);

    /**
    *   Writes the assembly code that effects the if-goto command.
    */
    void writeIf(const string& label);

    /**
    *   Writes the assembly code that effects the call command.
    */
    void writeCall(string functionName, int numArgs);

    /**
    *   Writes the assembly code that effects the return command.
    */
    void writeReturn();

    /**
    *   Writes the assembly code that effects the function command.
    */
    void writeFunction(string functionName, int numLocals);
    
private:
    ofstream& m_output;
    string m_fileName;
    string m_functionName;
    
   /* --------------------------------------------------------------------------
    *   Assembly-translation helper methods and members
    *   Each of the below methods writes an often-used piece of VM-logic to the
    *   output in assembly code.
    *   (Overwrites ?) means that the function overwrites the values currently 
    *   stored in the ? register.
    * ------------------------------------------------------------------------ */
    
    // label counters
    int m_eqLabel;
    int m_gtLabel;
    int m_ltLabel;
    int m_returnLabel;    

    /**
     *  Writes the assembly code for popping the stack to the D register.
     *  (Overwrites A and D)
     */
    void popToD();
    
    /**
     *  Writes the assembly code for decrementing the stack pointer.
     *  (Overwrites A)
     */
    void decSP();
    
    /**
     *  Writes the assembly code for incrementing the stack pointer.
     *  (Overwrites A)
     */
    void incSP();
    
    /**
     *  Sets the top of the stack to n. Do not call with A or M.
     *  (Overwrites A)
     */
    void setStack(string s);

    /**
     *  Push RAM[*seg + index] to stack.
     *  (Overwrites A and D)
     */
    void pushSegment(string seg, int index);
    
    /**
     *  Push RAM[base + index] to stack.
     *  (Overwrites A and D)
     */
    void pushFixedSegment(string base, int index);

    /**
     *  Simple push of *value to stack
     *  (Overwrites A and D)
     */
    void push(const char* value);
    
    /**
     *  Pop stack to RAM[*seg + index].
     *  (Overwrites A, D and RAM[13])
     */
    void popToSegment(string seg, int index);
    
    /**
     *  Pop stack to RAM[base + index].
     *  (Overwrites A, D and RAM[13])
     */
    void popToFixedSegment(string base, int index);

    /**
     *  Writes the comparison comp to the output, where comp is either EQ, GT, or LT.
     *  (Overwrites A and D)
     */
    void writeCompare(string comp, int& labelCounter);
   
};

#endif /* CODEWRITER_HPP */
