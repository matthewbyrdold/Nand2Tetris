/**
 *  File: CodeWriter.cpp
 *  
 *  Translates VM commands into Hack assembly code.
 *
 *  Author: matthew.james.bird@gmail.com
 */


#include <iostream>
#include <fstream>

#include "CodeWriter.hpp"

using namespace std;
using namespace vmt;

const string pointerBase = "3";
const string tempBase = "5";

int CodeWriter::eqLabel = 0;
int CodeWriter::gtLabel = 0;
int CodeWriter::ltLabel = 0;


CodeWriter::CodeWriter(ofstream& file)
    : m_output(file)
    , m_fileName("")
    , m_functionName("")
{}
    
CodeWriter::~CodeWriter()
{
    m_output.close();
}
    
/**    
 *  Informs the code writer that the translation of a new VM file has started.  
 */
void CodeWriter::setFileName(string file)
{
    m_fileName = file;
}

/**
*   Writes the assembly code that effects the VM initialisation (bootstrap code) 
*   place at the beginning of the output file.
*/
void CodeWriter::writeInit()
{
    m_output << "@0" << endl;
    m_output << "M = 256" << endl;
    // TODO: call Sys.init
}

/**
*   Writes the assembly code that effects the label command.
*/
void CodeWriter::writeLabel(const string& label)
{
    m_output << "(" << label << ")" << endl;
}

/**
*   Writes the assembly code that effects the goto command.
*/
void CodeWriter::writeGoto(const string& label)
{
    m_output << "@" << label << endl;
    m_output << "0;JMP" << endl;
}

/**
*   Writes the assembly code that effects the if-goto command.
*/
void CodeWriter::writeIf(const string& label)
{
    popToD();
    m_output << "@" << label << endl;
    m_output << "D;JNE" << endl;
}

/**
*   Writes the assembly code that effects the call command.
*/
void CodeWriter::writeCall(string functionName, int numArgs)
{
    //TODO
    // use case: call xxx
    // save caller's frame onto stack
    // (for return) push the address of the next command onto the stack (for return address)
    // allocate space for local variables of the called subroutine (xxx)
    // jump to execute code (@functionName, 0;JMP)
    //
    // PSEUDOCODE
    // push return address
    // push LCL
    // push ARG
    // push THIS
    // push THAT
    // ARG = SP - numArgs - 5
    // LCL = SP
    // goto functionName
    // (return-address)   // declare a label for return address
}

/**
*   Writes the assembly code that effects the return command.
*/
void CodeWriter::writeReturn()
{
    //TODO
    //
    // PSEUDOCODE
    // FRAME = LCL
    // RET = *(FRAME - 5)
    // *ARG = pop()
    // SP = ARG+1
    // THAT = *(FRAME-1)
    // THIS = *(FRAME-2)
    // ARG  = *(FRAME-3)
    // LCL  = *(FRAME-4)
    // goto RET
}

/**
*   Writes the assembly code that effects the function command.
*/
void CodeWriter::writeFunction(string functionName, int numLocals)
{
    //TODO
    // (f)   // declare a label for function entry
    // repeat numLocals times:
    //     push 0       // i.e. initialise locals to 0
}

/**   
 *  Writes the assembly code that is the translation of the given arithmetic command.  
 */
void CodeWriter::writeArithmetic(string command)
{   
    if (command == "add")
    {
        popToD();
        decSP();
        m_output << "M = D+M" << endl;
        incSP();
    }
    else if (command == "sub")
    {
        popToD();
        decSP();
        m_output << "M = M-D" << endl;
        incSP();
    }
    else if (command == "neg")
    {
        decSP();
        m_output << "M = -M" << endl;
        incSP();
    }
    else if (command == "eq")
    {
        writeCompare("EQ", eqLabel);
    }
    else if (command == "gt")
    {
        writeCompare("GT", gtLabel);
    }
    else if (command == "lt")
    {
        writeCompare("LT", ltLabel);
    }
    else if (command == "and")
    {
        popToD();
        decSP();
        m_output << "M = D&M" << endl;
        incSP();
    }
    else if (command == "or")
    {
        popToD();
        decSP();
        m_output << "M = D|M" << endl;
        incSP();
    }
    else if (command == "not")
    {
        popToD();
        m_output << "M = !D" << endl;
        incSP();
    }
}

/**
 *  Writes the assembly code that is the translation of the given command (either C_PUSH or C_POP)  
 */
void CodeWriter::writePushPop(command_t command, string segment, int index)
{
    if (command == C_PUSH)
    {
        if (segment == "constant")
        {
            m_output << "@" << index  << endl;
            m_output << "D = A"   << endl;
            setStack("D");
            incSP();
        }
        else if (segment == "local")
        {
            pushSegment("LCL", index);
        }
        else if (segment == "argument")
        {
            pushSegment("ARG", index);
        }
        else if (segment == "this")
        {
            pushSegment("THIS", index);
        }
        else if (segment == "that")
        {
            pushSegment("THAT", index);
        }
        else if (segment == "pointer")
        {
            pushFixedSegment(pointerBase, index);
        }
        else if (segment == "temp")
        {
            pushFixedSegment(tempBase, index);
        }
        else if (segment == "static")
        {
            m_output << "@" << m_fileName << "." << index << endl;
            m_output << "D = M" << endl;
            setStack("D");
            incSP();
        }
    }
    else if (command == C_POP)
    {
        if (segment == "local")
        {
            popToSegment("LCL", index);
        }
        else if (segment == "argument")
        {
            popToSegment("ARG", index);
        }
        else if (segment == "this")
        {
            popToSegment("THIS", index);
        }
        else if (segment == "that")
        {
            popToSegment("THAT", index);
        }
        else if (segment == "pointer")
        {
            popToFixedSegment(pointerBase, index);
        }
        else if (segment == "temp")
        {
            popToFixedSegment(tempBase, index);
        }
        else if (segment == "static")
        {
            popToD();
            m_output << "@" << m_fileName << "." << index << endl;
            m_output << "M = D" << endl;
        }
    }
}


/* ---------------------------------------------------------------------------------------------------
 *  Assembly-translation helper methods.
 *  Each of the below methods writes an often-used piece of VM-logic to the output in assembly code.
 *  (Overwrites ?) means that the function overwrites the values currently stored in the ? register.
 * --------------------------------------------------------------------------------------------------- */

/**
 *  Writes the assembly code for popping the stack to the D register.
 *  (Overwrites A and D)
 */
void CodeWriter::popToD()
{
    m_output << "@SP" << endl;
    m_output << "AM = M-1" << endl;
    m_output << "D = M" << endl;
}

/**
 *  Writes the assembly code for decrementing the stack pointer.
 *  (Overwrites A)
 */
void CodeWriter::decSP()
{
    m_output << "@SP"     << endl;
    m_output << "AM = M-1" << endl;
}

/**
 *  Writes the assembly code for incrementing the stack pointer.
 *  (Overwrites A)
 */
void CodeWriter::incSP()
{
    m_output << "@SP"     << endl;
    m_output << "AM = M+1" << endl;
}

/**
 *  Sets the top of the stack to n. Do not call with A or M.
 *  (Overwrites A)
 */
void CodeWriter::setStack(string s) 
{
    m_output << "@SP"         << endl;
    m_output << "AM = M"      << endl;
    m_output << "M = " << s   << endl;
}

/**
 *  Push RAM[*seg + index] to stack.
 *  (Overwrites A and D)
 */
void CodeWriter::pushSegment(string seg, int index)
{
    m_output << "@" << seg    << endl;
    m_output << "D = M"       << endl;
    m_output << "@" << index  << endl;
    m_output << "A = D+A"     << endl;
    m_output << "D = M"       << endl;
    setStack("D");
    incSP();
}

/**
 *  Push RAM[base + index] to stack.
 *  (Overwrites A and D)
 */
void CodeWriter::pushFixedSegment(string base, int index)
{
    m_output << "@" << base        << endl;
    m_output << "D = A"            << endl;
    m_output << "@" << index      << endl;
    m_output << "A = A+D"         << endl;
    m_output << "D = M"           << endl;
    setStack("D");
    incSP();
}

/**
 *  Pop stack to RAM[*seg + index].
 *  (Overwrites A, D and RAM[13])
 */
void CodeWriter::popToSegment(string seg, int index)
{
    m_output << "@" << seg    << endl;
    m_output << "D = M"       << endl;
    m_output << "@" << index  << endl;
    m_output << "D = D+A"     << endl;
    m_output << "@R13"        << endl;
    m_output << "M = D"       << endl;
    popToD();
    m_output << "@R13"        << endl;
    m_output << "A = M"       << endl;
    m_output << "M = D"       << endl;
}

/**
 *  Pop stack to RAM[base + index].
 *  (Overwrites A, D and RAM[13])
 */
void CodeWriter::popToFixedSegment(string base, int index)
{
    m_output << "@" << base       << endl;
    m_output << "D = A"           << endl;
    m_output << "@" << index      << endl;
    m_output << "D = A+D"         << endl;
    m_output << "@R13"            << endl;
    m_output << "M = D"           << endl;
    popToD();
    m_output << "@R13"            << endl;
    m_output << "A = M"           << endl;
    m_output << "M = D"           << endl;
}

/**
 *  Writes the comparison comp to the output, where comp is either EQ, GT, or LT.
 *  (Overwrites A and D)
 */
void CodeWriter::writeCompare(string comp, int& labelCounter)
{
    popToD();
    decSP();
    m_output << "D = M-D" << endl;
    m_output << "@" << comp << "_" << labelCounter << endl;
    m_output << "D;J" << comp << endl;
    setStack("0");
    m_output << "@" << comp << "_FIN_" << labelCounter << endl;
    m_output << "0;JMP" << endl;
    m_output << "(" << comp << "_" << labelCounter << ")" << endl;
    setStack("-1");
    m_output << "(" << comp << "_FIN_" << labelCounter << ")" << endl;
    incSP();
    
    ++labelCounter; 
}
