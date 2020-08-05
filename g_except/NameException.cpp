#include "NameException.h"

using std::string;
using graph::NameException;
using graph::VertexNameException;
using graph::GraphNameException;
using graph::GCFileNameException;

NameException::NameException(const string& error_message) : Exception("Invalid name -- ")
{
    this->error_message += error_message;
}

VertexNameException::VertexNameException(const string& error_message) : 
    NameException("vertex name error -- ")
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