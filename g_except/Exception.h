#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

namespace graph
{
    /**
     * base class for graph exceptions
     */
    class Exception : public std::exception
    {
    protected:
        std::string error_message;
    public:
        explicit Exception(const std::string& error_message = std::string("An unexpected error has occurred"));
        virtual ~Exception() = default;
        virtual const char* what() const noexcept override;
    };    
    
} // namespace graph



#endif // EXCEPTION_H
