#include "InstructionException.h"

using graph::InstructionException;
using graph::EmptyExpressionException;
using graph::BadCommandExpression;
using graph::UndefinedVariableException;
using graph::OperatorExceptoin;
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

UndefinedVariableException::UndefinedVariableException(const string& error_message) : 
    InstructionException("undefined variable -- ")
{
    this->error_message += error_message;
}


BadCommandExpression::BadCommandExpression(const string& error_message) : 
    InstructionException("unrecognized command -- ")
{
    this->error_message += error_message;
}

OperatorExceptoin::OperatorExceptoin(const string& error_message) : 
    InstructionException("bad operator -- ")
{
    this->error_message += error_message;
}