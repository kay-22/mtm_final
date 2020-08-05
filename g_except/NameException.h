#ifndef NAME_EXCEPTION_H
#define NAME_EXCEPTION_H

#include "Exception.h"

namespace graph
{
        
    class NameException : public Exception
    {
        
    public:
        NameException(const std::string& error_message = std::string(
                        "An unexpected error has occurred in Name module"));
        virtual ~NameException() = default;
    };

    class VertexNameException : public NameException
    {
    public:
        VertexNameException(const std::string& error_message = std::string(
                                "An unexpected error has occurred in VertexName module"));
        virtual ~VertexNameException() = default;
    };

    class GraphNameException : public NameException
    {
    public:
        GraphNameException(const std::string& error_message = std::string(
                                "An unexpected error has occurred in GraphName module"));
        virtual ~GraphNameException() = default;
    };

    class GCFileNameException : public NameException
    {
    public:
        GCFileNameException(const std::string& error_message = std::string(
                                "An unexpected error has occurred in GCFileName module"));
        virtual ~GCFileNameException() = default;
    };
    
} // namespace graph




#endif // NAME_EXCEPTION
