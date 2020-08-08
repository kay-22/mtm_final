#ifndef INSTRUCTION_EXCEPTION_H
#define INSTRUCTION_EXCEPTION_H

#include "Exception.h"

namespace graph
{
        
    class InstructionException : public Exception
    {
        
    public:
        InstructionException(const std::string& error_message = std::string(
                        "An unexpected error has occurred in Instruction module"));
        virtual ~InstructionException() = default;
    };

    class EmptyExpressionException : public InstructionException
    {
    public:
        EmptyExpressionException(const std::string& error_message);
        virtual ~EmptyExpressionException() = default;
    };

} // namespace graph




#endif // INSTRUCTION_EXCEPTION_H
