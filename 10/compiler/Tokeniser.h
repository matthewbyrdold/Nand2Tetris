/**   Tokeniser.h
 *    Splits Jack files into tokens.
 *    matthew.james.bird@gmail.com
 */

#ifndef tokeniser_h
#define tokeniser_h

enum TokenType {
    KEYWORD,
    SYMBOL,
    IDENTIFIER,
    INT_CONST,
    STRING_CONST,
}

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
}

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
     *  The token type of the current token.
     */
    TokenType tokenType();

    /** 
     *  The keyword which is the current token. 
     *  Should only be called when tokenType() is KEYWORD.
     */
    Keyword keyword();

    /**
     *  The character which is the current token.
     *  Should only be called when tokenType() is SYMBOL.
     */
    char symbol();

    /**
     *  The identifier which is the current token.
     *  Should only be called when tokenType() is IDENTIFIER.
     */
    const std::string& identifier();

    /**
     *  The integer value which is the current token.
     *  Should only be called when tokenType() is INT_CONST.
     */
    int intVal();

    /**
     *  The string which is the current token.
     *  Should only be called when tokenType() is STRING_CONST.
     */
    const std::string& stringVal();

private:
    std::string m_currentToken;
};

#endif // tokeniser_h    
