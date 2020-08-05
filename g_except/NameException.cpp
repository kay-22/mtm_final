#include "NameException.h"

using std::string;
using graph::NameException;
using graph::VerticeNameException;
using graph::GraphNameException;
using graph::GCFileNameException;

NameException::NameException(const string& error_message) : Exception("Invalid name -- ")
{
    this->error_message += error_message;
}

VerticeNameException::VerticeNameException(const string& error_message) : 
    NameException("vertice name error -- ")
{
    this->error_message += error_message;
}

GraphNameException::GraphNameException(const string& error_message) : 
    NameException("graph name error -- ")
{
    this->error_message += error_message;
}

GCFileNameException::GCFileNameException(const string& error_message) : 
    NameException("graph file name error -- ")
{
    this->error_message += error_message;
}