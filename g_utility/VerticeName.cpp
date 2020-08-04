#include "VerticeName.h"

using graph::VerticeName;
using std::string;

bool VerticeName::isValidCharacter(char ch)
{
    if (isalnum(ch) || (special_chars.find(ch) != special_chars.end())) {
        return true;
    }

    return false;
}