#include "GCFileName.h"

using graph::GCFileName;
using std::string;
using std::function;

GCFileName::GCFileName(const std::string& name) : Name(name)
{
    if (!isValidName()){
        //throw
    }
}

bool GCFileName::isValidName() const 
{
    function<bool(char)> anyChar = [](char){return true;};
    return name.isValid(anyChar, Parser::NO_ADDITIONAL, Parser::SpecialCharacters({'/', char(0)}));
}