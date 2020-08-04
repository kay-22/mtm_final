#include "VerticeName.h"

using graph::VerticeName;
using std::string;

VerticeName::VerticeName(const std::string& name) : Name(name), bracket_pattern('[', ']', ';') 
{
    if (!isValidName()){
        // TODO throw
    }
}

// bool VerticeName::isValidCharacter(char ch) const
// {
//     return isalnum(ch);
// }

bool VerticeName::isValidName() const
{
    if (!name.isValid(isalnum, bracket_pattern.toSpecialCharacters())) {
        return false;
    }
    if (name.isValid(isalnum, Parser::SpecialCharacters(), bracket_pattern.toSpecialCharacters())) {
        return true;
    }
    //TODO while.. find bracket patterns
    string::const_iterator left_it;

}

