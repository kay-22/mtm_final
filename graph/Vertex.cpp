#include "Vertex.h"

using graph::Vertex;
using std::string;


bool Vertex::operator<(const Vertex& other) const
{
    return name < other.name;
}

bool Vertex::operator==(const Vertex& other) const {
    return !((*this) < other) && !(other < (*this));
}



