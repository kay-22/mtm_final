#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <vector>
#include <utility>
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
        std::map<Vertex, std::set<const Vertex*>> graph;
        //std::vector<Vertex> getVertices() const; //needs Vertex() to work
    public:
        Graph(const std::string& name = std::string("unnamed")) : name(name), graph() {}
        Graph(const Graph&) = default;
        bool operator<(const Graph&) const;
        void addVertex(const Vertex&);
        void addEdge(const Vertex&, const Vertex&);
        bool containsVertex(const Vertex&) const;
        bool containsEdge(const Vertex&, const Vertex&) const;

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
