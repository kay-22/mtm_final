#ifndef VERTEX_H
#define VERTEX_H

#include "../g_utility/VertexName.h"


namespace graph
{
    //maybe this class is a bit redundant 
    class Vertex 
    {
    private:
        VertexName name;

    public:
        Vertex(const std::string& name) : name(name) {}
        Vertex(const Vertex&) = default;

        const BracketPattern& getBracketPattern() const;
        const std::string& getName() const;

        Vertex& operator=(const Vertex&) = default;
        bool operator<(const Vertex&) const;
        bool operator==(const Vertex&) const;

        ~Vertex() = default;
    };
}

#endif 