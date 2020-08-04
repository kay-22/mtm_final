#include "GCFileName.h"

using graph::GCFileName;
using std::string;

bool GCFileName::isValidCharacter(char ch)
{
    if (special_chars.find(ch) != special_chars.end()) {
        return false;
    }

    return true;
}