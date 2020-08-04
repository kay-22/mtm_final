#include "Vertice.h"

using graph::Vertice;
using std::string;


bool Vertice::operator<(const Vertice& other)
{
    return name < other.name;
}



