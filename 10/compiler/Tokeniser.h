/**   Tokeniser.h
 *    Splits Jack files into tokens.
 *    matthew.james.bird@gmail.com
 */

#ifndef tokeniser_h
#define tokeniser_h

#include <iostream>
#include <fstream>

// Undefine C macros as we use them as keywords
#undef NULL
#undef TRUE
#undef FALSE

enum TokenType 
{
    KEYWORD,
    SYMBOL,
    IDENTIFIER,
    INT_CONST,
    STRING_CONST,
};

enum Keyword {
    CLASS,
    METHOD,
    FUNCTION,
    CONSTRUCTOR,
    INT,
    BOOLEAN,
    CHAR,
    VOID,
    VAR,
    STATIC,
    FIELD,
    LET,
    DO,
    IF,
    ELSE,
    WHILE,
    RETURN,
    TRUE,
    FALSE,
    NULL,
    THIS,
};

/** 
 * Removes all comments and whitespace from the input stream and breaks it into
 * Jack-language tokens, as specified by the Jack-grammar.
 */
class Tokeniser {
public:
    Tokeniser(std::ifstream&);
    ~Tokeniser();
    
    /** Skips whitespace and comments and advances to the next token */
    bool hasMoreTokens();

    /** 
     *  Gets the next token from the input and makes it the current token.
     *  Should only be called if hasMoreTokens(). Initially there is no token.
     */
    void advance();

    /** The type of the current token. */
    TokenType tokenType();

    /** The following methods return the token of type T, and should only be
     *  called when tokenType() is the corresponding type (i.e., keyword() 
     *  requires that the tokenType() == KEYWORD)
     */
    Keyword            keyword();
    char               symbol();
    const std::string& identifier();
    int                intVal();
    const std::string& stringVal();

private:
    Tokeniser();

    std::string m_currentToken;

    std::ifstream& m_inputFile; 
};

#endif // tokeniser_h    
