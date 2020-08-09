#include "VertexName.h"

using graph::VertexName;
using graph::VertexNameException;
using graph::Name;
using std::string;

VertexName::VertexName(const std::string& name) : Name(name), bracket_pattern('[', ']', ';') 
{
    if (name.empty()) {
        throw VertexNameException("name cannot be empty.");
    }
    if (!isValidName()){
        throw VertexNameException("'" + name + "'");
    }
    
}

bool VertexName::isValidName() const
{
    if (!name.isValid(isalnum, bracket_pattern.toSpecialCharacters())) {
        return false;
    }
    if (name.isValid(isalnum, Parser::NO_ADDITIONAL, bracket_pattern.toSpecialCharacters())) {
        return true;
    }
    
    return name.isMatchingSequence(bracket_pattern);

}
