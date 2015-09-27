/**
 *	Header file for virtual machine translator.
 */

#ifndef VMT_HPP

namespace vmt 
{
	enum command_t {C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL};
}

#endif	/* VMT_HPP */