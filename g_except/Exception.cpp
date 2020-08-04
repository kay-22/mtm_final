#include "Exception.h"

using graph::Exception;
using std::string;

Exception::Exception(const string& error_message) : error_message("Error: ")
{
    this->error_message += error_message;
}

const char* Exception::what() const noexcept
{
    return error_message.c_str();
}