#include "Name.h"

using graph::Name;
using graph::Exception;
using std::string;
using std::unordered_set;

bool Name::operator<(const Name& other) const
{
    return name < other.name;
}

const string& Name::toString() const
{
    return name.getData();
}