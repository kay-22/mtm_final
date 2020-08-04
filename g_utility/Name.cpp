#include "Name.h"

using graph::Name;
using std::string;
using std::unordered_set;

Name::Name(const string& name, const SpecialCharacters& special_chars) : name(), special_chars(special_chars)
{
    if (isValidNameString(name)) {
        this->name = name;
    }
    else {
        //thwor except
    }
}
bool Name::isValidNameString(const std::string& name_string)
{
    for (char ch : name_string) {
        if (!isValidCharacter(ch)) {
            return false;
        }
    }

    return true;
}

bool Name::operator<(const Name& other)
{
    return name < other.name;
}

const string& Name::toString()
{
    return name;
}