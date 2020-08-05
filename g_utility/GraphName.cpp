#include "GraphName.h"

using graph::GraphName;
using graph::Name;

GraphName::GraphName(const std::string& name) : Name(name) 
{
    if (!isValidName()){
        //throw
    }
}

bool GraphName::isValidName() const 
{
    return name.isValid(); //defualt values of name.isValid() are appropriate. checks if characters are alphanumeric 
}