/**   Tokeniser.cpp
 *    Splits Jack files into tokens.
 *    matthew.james.bird@gmail.com
 */

#include <Tokeniser.h>

#include <vector>
std::vector<const char*> elements = {"(", ")", "[", "]", "{", "}", ",", ";", "=", ".", "+",
                          "-", "*", "/", "&", "|", "~", "<", ">", "class", 
                          "constructor", "method", "function", "int", "boolean",
                          "char", "void", "var", "static", "field", "let", "do",
                          "if", "else", "while", "return", "true", "false",
                          "null", "this"};

std::vector<const char*> symbols = {"(", ")", "[", "]", "{", "}", ",", ";", "=", ".", "+",
                                  "-", "*", "/", "&", "|", "~", "<", ">"};

bool isSymbol(char c)
{
    for (auto symbol : symbols)
    {
        if (c == *symbol)
        {
            return true;
        }
    }
    return false;
}

Tokeniser::Tokeniser(std::ifstream& input)
    : m_inputFile(input)
{
    std::string word;
    while (hasMoreTokens())
    {
        m_inputFile >> word;
        std::cout << word << std::endl;
    }
}

Tokeniser::~Tokeniser()
{
}

bool Tokeniser::hasMoreTokens()
{
    char c;
    char nextChar;
    bool singleLineComment = false;
    bool multiLineComment = false; // treat /** API comments */ the same
    while (true)
    {
        m_inputFile.get(c);
        if (m_inputFile.eof())
        {
            return false;
        }

        nextChar = m_inputFile.peek();
        if (c == '\n')
        {
            singleLineComment = false;
        }
        else if (c == '*' && nextChar == '/')
        {
            multiLineComment = false;
            m_inputFile.get(c);
        }
        else if (c == '/' && nextChar == '/')
        {
            singleLineComment = true;
            m_inputFile.get(c);
        }
        else if (c == '/' && nextChar == '*')
        {
            multiLineComment = true;
            m_inputFile.get(c);
        }
        else if (!singleLineComment && !multiLineComment && !isspace(c))
        {
            m_inputFile.putback(c);
            return true; 
        }
    }
}

