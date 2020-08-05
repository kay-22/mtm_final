#include "GraphName.h"

using graph::GraphName;
using graph::GraphNameException;
using graph::Name;

GraphName::GraphName(const std::string& name) : Name(name) 
{
    if (name.empty()) {
        throw GraphNameException("name cannot be empty.");
    }
    if (!isValidName()){
        throw GraphNameException("failed creating GraphName. Graph names are allowed to be only alphanumeric and "
                                 "cannot start with a digit.");
    }
}

bool GraphName::isValidName() const 
{
    return !isdigit(name.getData().at(0)) && name.isValid(); //defualt values of name.isValid() are appropriate. checks if characters are alphanumeric 
}