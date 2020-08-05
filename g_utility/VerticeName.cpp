#include "VerticeName.h"

using graph::VerticeName;
using graph::VerticeNameException;
using graph::Name;
using std::string;

VerticeName::VerticeName(const std::string& name) : Name(name), bracket_pattern('[', ']', ';') 
{
    if (!isValidName()){
        throw VerticeNameException("failed creating VerticeName. A valid vertice name consists of "
                                    "alphanumeric characters and '[', ']', and ';'. The brackets must "
                                    "form a matching sequence, and the delimiter ';' can only be between brackets.");
    }
    
}

bool VerticeName::isValidName() const
{
    if (!name.isValid(isalnum, bracket_pattern.toSpecialCharacters())) {
        return false;
    }
    if (name.isValid(isalnum, Parser::NO_ADDITIONAL, bracket_pattern.toSpecialCharacters())) {
        return true;
    }
    
    return name.isMatchingSequence(bracket_pattern);

}

