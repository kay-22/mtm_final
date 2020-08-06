#include "Vertex.h"

using graph::Vertex;
using graph::BracketPattern;
using std::string;

const BracketPattern& Vertex::getBracketPattern() const
{
    return name.bracket_pattern;
}

const string& Vertex::getName() const 
{
    return name.toString();
}

bool Vertex::operator<(const Vertex& other) const
{
    return name < other.name;
}

bool Vertex::operator==(const Vertex& other) const {
    return !((*this) < other) && !(other < (*this));
}



