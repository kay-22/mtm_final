#include "InstructionException.h"

using graph::InstructionException;
using graph::EmptyExpressionException;
using graph::BadCommandExpression;
using graph::UndefinedVariableException;
using graph::OperatorException;
using graph::FileException;
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

OperatorException::OperatorException(const string& error_message) : 
    InstructionException("bad operator -- ")
{
    this->error_message += error_message;
}

FileException::FileException(const string& error_message) : 
    InstructionException("file error -- ")
{
    this->error_message += error_message;
}