/**   Tokeniser.h
 *    Splits Jack files into tokens.
 *    matthew.james.bird@gmail.com
 */

#ifndef tokeniser_h
#define tokeniser_h

#include <iostream>

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
    Tokeniser();
    ~Tokeniser();
    
    bool hasMoreTokens();

    /** 
     *  Gets the next token from the input and makes it the current token.
     *  Should only be called if hasMoreTokens(). Initially there is no token.
     */
    void advance();

    /**
     *  The type of the current token.
     */
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
    std::string m_currentToken;
};

#endif // tokeniser_h    
