#ifndef GRAPH_EXCEPTION_H
#define GRAPH_EXCEPTION_H

#include "Exception.h"

namespace graph
{
    class GraphException : public Exception 
    {
           
    public:
        GraphException(const std::string& error_message = std::string(
                        "An unexpected error has occurred in Graph module"));
        virtual ~GraphException() = default;
    };

    class GraphExsitingElementException : public GraphException
    {
    public:
        GraphExsitingElementException(const std::string& error_message);
        virtual ~GraphExsitingElementException() = default;
    };

    class GraphNoElementException : public GraphException
    {
    public:
        GraphNoElementException(const std::string& error_message);
        virtual ~GraphNoElementException() = default;
    };
} // namespace graph


#endif // GRAPH_EXCEPTION_H
