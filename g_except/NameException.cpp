#include "NameException.h"

using std::string;
using graph::NameException;

NameException::NameException(const string& error_message) : Exception("Invalid name -- ")
{
    this->error_message += error_message;
}