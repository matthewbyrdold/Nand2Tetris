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

CodeWriter::CodeWriter(ofstream& file)
    : m_output(file)
    , m_fileName("")
    , m_functionName("")
    , m_eqLabel(0)
    , m_gtLabel(0)
    , m_ltLabel(0)
    , m_returnLabel(0)
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
    m_output << "// Translation of VM class [" << file << "]" << endl;
    m_fileName = file;
}

/**
*   Writes the assembly code that effects the VM initialisation (bootstrap code) 
*   place at the beginning of the output file.
*/
void CodeWriter::writeInit()
{
    m_output << "// VMTRANSLATION: BOOTSTRAP" << endl;
    // setting up stack pointer
    m_output << "@256" << endl;
    m_output << "D = A" << endl;
    m_output << "@SP" << endl;
    m_output << "M = D" << endl;

    writeCall("Sys.init", 0);
}

/**
*   Writes the assembly code that effects the label command.
*/
void CodeWriter::writeLabel(const string& label)
{
    m_output << "(" << m_functionName << "$" << label << ")" << endl;
}

/**
*   Writes the assembly code that effects the goto command.
*/
void CodeWriter::writeGoto(const string& label)
{
    m_output << "// goto " << label << endl;
    m_output << "@" << m_functionName << "$" << label << endl;
    m_output << "0;JMP" << endl;
}

/**
*   Writes the assembly code that effects the if-goto command.
*/
void CodeWriter::writeIf(const string& label)
{
    m_output << "// if go-to " << label << endl;
    popToD();
    m_output << "@" << m_functionName << "$" << label << endl;
    m_output << "D;JNE" << endl;
}

/**
*   Writes the assembly code that effects the call command.
*/
void CodeWriter::writeCall(string functionName, int numArgs)
{
    m_output << "// Calling " << functionName << " " << numArgs << endl;
   
    // Push return addr  // TODO: val or addr?
    m_output << "@return-address" << m_returnLabel << endl;
    m_output << "D = A" << endl;
    m_output << "@SP" << endl;
    m_output << "A = M" << endl;
    m_output << "M = D" << endl;
    incSP();

    // push current frame
    push("LCL");
    push("ARG");
    push("THIS");
    push("THAT");

    // ARG = SP - numArgs - 5
    m_output << "@SP" << endl;
    m_output << "D = M" << endl;
    m_output << "@" << numArgs << endl;
    m_output << "D = D - A" << endl;
    m_output << "@5" << endl;
    m_output << "D = D - A" << endl;
    m_output << "@ARG" << endl;
    m_output << "M = D  // ARG = SP - numArgs - 5" << endl;
    
    // LCL = SP
    m_output << "@SP" << endl;
    m_output << "D = M" << endl;
    m_output << "@LCL" << endl;
    m_output << "M = D  // LCL = SP" << endl;

    // goto functionName
    m_output << "@" << functionName << endl;
    m_output << "0;JMP  // Goto " << functionName << endl;

    m_output << "(return-address" << m_returnLabel << ")" << endl;
    ++m_returnLabel;
}

/**
*   Writes the assembly code that effects the return command.
*/
void CodeWriter::writeReturn()
{
    m_output << "// Return" << endl;

    // frame = LCL
    m_output << "@LCL" << endl;
    m_output << "D = M" << endl;
    m_output << "@frame" << endl;
    m_output << "M = D  // frame = LCL" << endl;

    // ret = *(frame - 5)   where ret = return addr
    m_output << "@frame" << endl;
    m_output << "D = M" << endl;
    m_output << "@5" << endl;
    m_output << "A = D - A" << endl;
    m_output << "D = M" << endl;
    m_output << "@ret" << endl;
    m_output << "M = D  // ret = *(frame - 5)" << endl;

    // *ARG = pop()
    popToD();
    m_output << "@ARG" << endl;
    m_output << "A = M" << endl;
    m_output << "M = D  // *ARG = pop()" << endl;

    // SP = ARG+1
    m_output << "@ARG" << endl;
    m_output << "D = M + 1" << endl;
    m_output << "@SP" << endl;
    m_output << "M = D  // SP = ARG+1" << endl;

    // THAT = *(frame-1)    // TODO: common code: pull out into func
    m_output << "@frame" << endl;
    m_output << "D = M" << endl;
    m_output << "@1" << endl;
    m_output << "A = D - A" << endl;
    m_output << "D = M" << endl;
    m_output << "@THAT" << endl;
    m_output << "M = D  // THAT = *(frame-1)" << endl;

    // THIS = *(frame-2)
    m_output << "@frame" << endl;
    m_output << "D = M" << endl;
    m_output << "@2" << endl;
    m_output << "A = D - A" << endl;
    m_output << "D = M" << endl;
    m_output << "@THIS" << endl;
    m_output << "M = D  // THIS = *(frame-2)" << endl;
    
    // ARG  = *(frame-3)
    m_output << "@frame" << endl;
    m_output << "D = M" << endl;
    m_output << "@3" << endl;
    m_output << "A = D - A" << endl;
    m_output << "D = M" << endl;
    m_output << "@ARG" << endl;
    m_output << "M = D  // ARG = *(frame-3)" << endl;
    
    // LCL  = *(frame-4)
    m_output << "@frame" << endl;
    m_output << "D = M" << endl;
    m_output << "@4" << endl;
    m_output << "A = D - A" << endl;
    m_output << "D = M" << endl;
    m_output << "@LCL" << endl;
    m_output << "M = D  // LCL = *(frame-4)" << endl;
    
    // goto ret
    m_output << "@ret" << endl;
    m_output << "A = M" << endl;
    m_output << "0;JMP  // goto ret" << endl; 
}

/**
*   Writes the assembly code that effects the function command.
*/
void CodeWriter::writeFunction(string functionName, int numLocals)
{
    m_output << "// Defining function " << functionName << " " << numLocals << endl;
    m_functionName = functionName;

    m_output << "(" << functionName << ")" << endl;
    // initialise arguments to 0
    for (int i = 0; i < numLocals; ++i)
    {
        // push 0
        m_output << "@0" << endl;
        m_output << "D = A" << endl;
        m_output << "@SP" << endl;
        m_output << "A = M" << endl;
        m_output << "M = D" << endl;
        incSP();
    }
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
        writeCompare("EQ", m_eqLabel);
    }
    else if (command == "gt")
    {
        writeCompare("GT", m_gtLabel);
    }
    else if (command == "lt")
    {
        writeCompare("LT", m_ltLabel);
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
            m_output << "// push constant " << index << endl;
            m_output << "@" << index  << endl;
            m_output << "D = A"   << endl;
            setStack("D");
            incSP();
        }
        else if (segment == "local")
        {
            m_output << "// push local " << index << endl;
            pushSegment("LCL", index);
        }
        else if (segment == "argument")
        {
            m_output << "// push argument " << index << endl;
            pushSegment("ARG", index);
        }
        else if (segment == "this")
        {
            m_output << "// push this " << index << endl;
            pushSegment("THIS", index);
        }
        else if (segment == "that")
        {
            m_output << "// push that " << index << endl;
            pushSegment("THAT", index);
        }
        else if (segment == "pointer")
        {
            m_output << "// push pointer " << index << endl;
            pushFixedSegment(pointerBase, index);
        }
        else if (segment == "temp")
        {
            m_output << "// push temp " << index << endl;
            pushFixedSegment(tempBase, index);
        }
        else if (segment == "static")
        {
            m_output << "// push static " << index << endl;
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
            m_output << "// pop local " << index << endl;
            popToSegment("LCL", index);
        }
        else if (segment == "argument")
        {
            m_output << "// pop argument " << index << endl;
            popToSegment("ARG", index);
        }
        else if (segment == "this")
        {
            m_output << "// pop this " << index << endl;
            popToSegment("THIS", index);
        }
        else if (segment == "that")
        {
            m_output << "// pop that " << index << endl;
            popToSegment("THAT", index);
        }
        else if (segment == "pointer")
        {
            m_output << "// pop pointer " << index << endl;
            popToFixedSegment(pointerBase, index);
        }
        else if (segment == "temp")
        {
            m_output << "// pop temp " << index << endl;
            popToFixedSegment(tempBase, index);
        }
        else if (segment == "static")
        {
            m_output << "// pop static " << index << endl;
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
 *  Simple push of *value to the stack.
 */
void CodeWriter::push(const char* value)
{
    m_output << "@" << value << endl;
    m_output << "D = M" << endl;
    m_output << "@SP" << endl;
    m_output << "A = M" << endl;
    m_output << "M = D  // push " << value << endl;
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
