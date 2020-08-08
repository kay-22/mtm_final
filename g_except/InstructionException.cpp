#include "InstructionException.h"

using graph::InstructionException;
using graph::EmptyExpressionException;
using std::string;


InstructionException::InstructionException(const string& error_message) : Exception("execute error -- ")
{
    this->error_message += error_message;
}

EmptyExpressionException::EmptyExpressionException(const string& error_message) : 
    InstructionException("empty expressions are not allowed -- ")
{
    this->error_message += error_message;
}