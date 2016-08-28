/**   JackStatus.h
 *    Status codes for the Jack Compiler.
 *    matthew.james.bird@gmail.com
 */

#ifndef jackstatus_h
#define jackstatus_h

enum JackStatus
{
    Success,
    EndOfData,
    PrematureEnd,
    ParseFailure,
    FileAccessFailure,
};

#endif // jackstatus_h    
