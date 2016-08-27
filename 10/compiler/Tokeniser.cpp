/**   Tokeniser.cpp
 *    Splits Jack files into tokens.
 *    matthew.james.bird@gmail.com
 */

#include <Tokeniser.h>

#include <vector>

static const std::vector<const char*> 
keywords = {"class", "constructor", "method", "function", "int", "boolean",
            "char", "void", "var", "static", "field", "let", "do", "if",
            "else", "while", "return", "true", "false", "null", "this"};

static const std::vector<const char*>
symbols = {"(", ")", "[", "]", "{", "}", ",", ";", "=", ".", "+", "-", "*", "/",
           "&", "|", "~", "<", ">"};

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

using std::cout; using std::endl;
Tokeniser::Tokeniser(std::ifstream& input)
    : m_inputFile(input)
{
    // ALL OF THIS IS TEST CODE.
    std::string word;
    cout << "<tokens>" << endl;
    while (hasMoreTokens())
    {
        advance();
        TokenType type = tokenType();
        switch (type)
        {
        case KEYWORD:
            keyword();
            cout << "<keyword> " << m_currentToken << " </keyword>" << endl; 
            break;
        case SYMBOL:
        {
            std::string xmlSafeSymbol = "";
            xmlSafeSymbol += symbol();
            if (xmlSafeSymbol == "<")
                xmlSafeSymbol = "&lt;";
            else if (xmlSafeSymbol == ">")
                xmlSafeSymbol = "&gt;";
            else if (xmlSafeSymbol == "&")
                xmlSafeSymbol = "&amp;"; 
            cout << "<symbol> " << xmlSafeSymbol << " </symbol>" << endl;
            break;
        }
        case IDENTIFIER:
            cout << "<identifier> " << identifier() << " </identifier>" << endl;
           break;
        case INT_CONST:
            cout << "<integerConstant> " << intVal() << " </integerConstant>" << endl;
            break;
        case STRING_CONST:
            cout << "<stringConstant> " << stringVal() << " </stringConstant>" << endl;
            break;
        default:
            cout << "ERROR" << endl;  
        }
    }
    cout << "</tokens>" << endl;
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

void Tokeniser::advance()
{
    std::string tempToken;
    char c;
    char nextC;
    bool cIsSymbol;
    while (!m_inputFile.eof())
    {
        m_inputFile.get(c);
        nextC = m_inputFile.peek();
        cIsSymbol = isSymbol(c);

        if (c == '\"')
        {
            // it's a string -- get it all
            while (!m_inputFile.eof())
            {
                m_inputFile.get(c);
                if (c == '\"')
                {
                    break;
                }
                else
                {
                    tempToken += c;
                }
            } 
            m_currentToken = tempToken;
            m_currentTokenType = STRING_CONST;
            return; 
        }

        if (cIsSymbol && tempToken.size() == 0)
        {
            for (auto symbol : symbols)
            {
                if (c == *symbol)
                {
                    m_currentToken = c;
                    m_currentTokenType = SYMBOL;
                    return;
                }
            }
        }
        else if (isspace(c) || cIsSymbol)
        {
            if (cIsSymbol) m_inputFile.putback(c);
            // Keyword?
            for (auto word : keywords)
            {
                if (tempToken == word)
                {
                    m_currentToken = tempToken;
                    m_currentTokenType = KEYWORD;
                    return;
                }
            }
            // Integer constant?
            bool isNumber = !tempToken.empty()
                          && std::find_if(tempToken.begin(), 
                                          tempToken.end(), 
                                          [](char c) {return !std::isdigit(c);}) 
                             == tempToken.end();
            if (isNumber)
            {
                m_currentToken = tempToken;
                m_currentTokenType = INT_CONST;
            } 
            // Identifier?
            else if (tempToken[0] == '_' || isalpha(tempToken[0]))
            {
                m_currentToken = tempToken;
                m_currentTokenType = IDENTIFIER;
            }
            else
            {
                std::cerr << "Cannot tokenise " << tempToken
                          << "(identifiers must begin with a-zA-Z or '_')" << std::endl;
            }
            return;
        }
        else
        {
            tempToken += c;
        }
    }
}

TokenType Tokeniser::tokenType()
{
    return m_currentTokenType;
}

Keyword Tokeniser::keyword()
{
    if (m_currentToken == "class")
        return CLASS;
    
    else if (m_currentToken == "method")
        return METHOD;

    else if (m_currentToken == "function")
        return FUNCTION;

    else if (m_currentToken == "constructor")
        return CONSTRUCTOR;

    else if (m_currentToken == "int")
        return INT;

    else if (m_currentToken == "boolean")
        return BOOLEAN;

    else if (m_currentToken == "char")
        return CHAR;

    else if (m_currentToken == "void")
        return VOID;
    
    else if (m_currentToken == "var")
        return VAR;

    else if (m_currentToken == "static")
        return STATIC;

    else if (m_currentToken == "field")
        return FIELD;

    else if (m_currentToken == "let")
        return LET;

    else if (m_currentToken == "do")
        return DO;

    else if (m_currentToken == "if")
        return IF;

    else if (m_currentToken == "else")
        return ELSE;

    else if (m_currentToken == "while")
        return WHILE;

    else if (m_currentToken == "return")
        return RETURN;

    else if (m_currentToken == "true")
        return TRUE;

    else if (m_currentToken == "false")
        return FALSE;

    else if (m_currentToken == "null")
        return NULL;

    else if (m_currentToken == "this")
        return THIS;

    else
    {
        std::cerr << "ERROR: unrecognised keyword " << m_currentToken << std::endl;
        return ERROR_LAST_KEYWORD;
    }
}

char Tokeniser::symbol()
{
    return m_currentToken[0];
}

const std::string& Tokeniser::identifier()
{
    return m_currentToken;
}

int Tokeniser::intVal()
{
    return atoi(m_currentToken.c_str());
}

const std::string& Tokeniser::stringVal()
{
    return m_currentToken;
}

