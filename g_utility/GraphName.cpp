#include "GraphName.h"

using graph::GraphName;
using graph::Name;

bool GraphName::isValidCharacter(char ch)
{
    return isalnum(ch);
}