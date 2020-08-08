#include "ParserException.h"

using graph::ParserException;
using graph::GraphLiteralParserException;
using graph::MatchingSequenceParserException;
using std::string;


ParserException::ParserException(const string& error_message) : Exception("parser error -- ")
{
    this->error_message += error_message;
}

GraphLiteralParserException::GraphLiteralParserException(const string& error_message) : 
    ParserException("could not parse graph literal -- ")
{
    this->error_message += error_message;
}

MatchingSequenceParserException::MatchingSequenceParserException(const string& error_message) : 
    ParserException("could not parse matching sequence -- ")
{
    this->error_message += error_message;
}