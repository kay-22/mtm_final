#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

#include "Vertex.h"
#include <g_utility.h>

namespace graph
{
    class Graph
    {
    private:
        GraphName name;
        std::map<Vertex, std::set<Vertex*>> graph;
        //std::vector<Vertex> getVertices() const; //needs Vertex() to work
    public:
        Graph(const std::string& name = std::string("unnamed")) : name(name), graph() {}
        Graph(const Graph&) = default;
        bool operator<(const Graph&) const;
        void addVertex(const Vertex&);
        void addEdge(const Vertex&, const Vertex*);

        Graph& operator=(const Graph&) = default;
        //Graph& operator+=(const Graph&);
        //maybe implement ^= -= += and make binary non-member
        //idont think i need binary ops if no other types are needed to be casted (rip engligh)
        Graph operator+(const Graph&) const;
        Graph operator^(const Graph&) const;
        Graph operator-(const Graph&) const;
        Graph operator*(const Graph&) const;
        Graph operator!() const;

        ~Graph() = default;
    }; 
} // namespace graph

#endif // GRAPH_H
