#ifndef PARSER_EXCEPTION_H
#define PARSER_EXCEPTION_H

#include "Exception.h"

namespace graph
{
        
    class ParserException : public Exception
    {
        
    public:
        ParserException(const std::string& error_message = std::string(
                        "An unexpected error has occurred in Parser module"));
        virtual ~ParserException() = default;
    };

    class GraphLiteralParserException : public ParserException
    {
    public:
        GraphLiteralParserException(const std::string& error_message);
        virtual ~GraphLiteralParserException() = default;
    };

    class MatchingSequenceParserException : public ParserException
    {
    public:
        MatchingSequenceParserException(const std::string& error_message);
        virtual ~MatchingSequenceParserException() = default;
    };

} // namespace graph




#endif // PARSER_EXCEPTION_H
