#ifndef VERTICE_H
#define VERTICE_H

#include <g_utility.h>

namespace graph
{
    class Vertice 
    {
    private:
        VerticeName name;

    public:
        Vertice(const std::string& name) : name(name) {}
        Vertice(const Vertice&) = default;
        Vertice& operator=(const Vertice&) = default;
        bool operator<(const Vertice&);
        ~Vertice() = default;
    };
}

#endif 