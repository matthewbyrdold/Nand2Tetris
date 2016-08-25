/**   Tokeniser.cpp
 *    Splits Jack files into tokens.
 *    matthew.james.bird@gmail.com
 */

#include <Tokeniser.h>

Tokeniser::Tokeniser(std::ofstream& input)
    : m_inputFile(input)
{
}

Tokeniser::~Tokeniser()
{
}
