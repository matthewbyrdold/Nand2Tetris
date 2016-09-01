/**   Tokeniser.h
 *    Splits Jack files into tokens.
 *    matthew.james.bird@gmail.com
 */

#ifndef tokeniser_h
#define tokeniser_h

#include "JackStatus.h"

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
    ERROR_LAST_KEYWORD
};

/** 
 * Removes all comments and whitespace from the input stream and breaks it into
 * Jack-language tokens, as specified by the Jack-grammar.
 */
class Tokeniser {
public:
    Tokeniser(std::ifstream&, std::string);
    ~Tokeniser();
    
    /** Skips whitespace and comments and advances to the next token */
    bool hasMoreTokens() const;

    /** 
     *  Checks whether hasMoreTokens() (returns false if not, otherwise...)
     *  Gets the next token from the input and makes it the current token.
     *  Should only be called if hasMoreTokens(). Initially there is no token.
     */
    bool advance();

    /** The type of the current token. */
    TokenType tokenType() const;

    /** The following methods return the token of type T, and should only be
     *  called when tokenType() is the corresponding type (i.e., keyword() 
     *  requires that the tokenType() == KEYWORD)
     */
    Keyword            keyword()    const;
    char               symbol()     const;
    const std::string& identifier() const;
    int                intVal()     const;
    const std::string& stringVal()  const;

    const std::string& currentToken() const;

    /** Used for compiler error outputting */
    uint32_t lineNumber() {return m_lineNumber;}
    const std::string& filename() {return m_filename;}

    /** Look ahead function: saves the current position in the input file, and 
     * the current token information, reads the next token, restores the position 
     * in the input file and the token information and returns the next token.
     */
    std::string nextToken();

private:
    Tokeniser();

    std::string m_currentToken;
    TokenType m_currentTokenType;

    std::ifstream& m_inputFile; 
    std::string m_filename;
    mutable uint32_t m_lineNumber;
};

#endif // tokeniser_h    
