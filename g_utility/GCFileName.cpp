#include "GCFileName.h"

using graph::GCFileName;
using graph::GCFileNameException;
using graph::Name;
using std::string;
using std::function;

GCFileName::GCFileName(const std::string& name) : Name(name)
{
    if (name.empty()) {
        throw GCFileNameException("name cannot be empty.");
    }
    if (!isValidName()){
        throw GCFileNameException("file name cannot include '/', ',', '(', ')', and char(0)."); //testwith '/'
    }
}

bool GCFileName::isValidName() const 
{
    function<bool(char)> anyChar = [](char){return true;};
    return name.isValid(anyChar, Parser::NO_ADDITIONAL, Parser::SpecialCharacters({'/', ',', '(', ')', char(0)}));
}