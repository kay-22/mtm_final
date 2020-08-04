#ifndef NAME_EXCEPTION
#define NAME_EXCEPTION

#include "Exception.h"

namespace graph
{
        
    class NameException : public Exception
    {
        
    public:
        NameException(const std::string& error_message = std::string("An unexpected error has occurred in Name module"));
        virtual ~NameException() = default;
    };
} // namespace graph




#endif // NAME_EXCEPTION
