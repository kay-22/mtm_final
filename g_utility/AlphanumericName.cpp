#include "AlphanumericName.h"

using graph::AlphanumericName;
using graph::Name;

bool AlphanumericName::isValidCharacter(char ch)
{
    return isalnum(ch);
}