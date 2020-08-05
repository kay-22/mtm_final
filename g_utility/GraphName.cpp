#include "GraphName.h"

using graph::GraphName;
using graph::GraphNameException;
using graph::Name;

GraphName::GraphName(const std::string& name) : Name(name) 
{
    if (!isValidName()){
        throw GraphNameException("failed creating GraphName. Graph names are allowed to be only alphanumeric.");
    }
}

bool GraphName::isValidName() const 
{
    return name.isValid(); //defualt values of name.isValid() are appropriate. checks if characters are alphanumeric 
}