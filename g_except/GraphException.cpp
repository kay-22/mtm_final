#include "GraphException.h"

using graph::Exception;
using graph::GraphException;
using graph::GraphExsitingElementException;
using graph::GraphNoElementException;
using std::string;


GraphException::GraphException(const string& error_message) : Exception("graph error -- ")
{
    this->error_message += error_message;
}

GraphExsitingElementException::GraphExsitingElementException(const string& error_message) : 
    GraphException("cannot add existing element -- ")
{
    this->error_message += error_message;
}

GraphNoElementException::GraphNoElementException(const string& error_message) : 
    GraphException("no such element in the graph -- ")
{
    this->error_message += error_message;
}