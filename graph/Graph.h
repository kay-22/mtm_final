#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <ostream>

#include "Vertex.h"
#include <g_utility.h>
#include <g_except.h>

namespace graph
{
    
    typedef std::pair<Vertex, Vertex> Edge;
    //typdef std::map<Vertex, std::set<Vertex>> GraphData;
    class Graph
    {
    private:
        GraphName name;
        std::map<Vertex, std::set<Vertex>> data; //maybe typedef to GraphData or set<Vertex> to VertexOutData
        //std::vector<Vertex> getVertices() const; //needs Vertex() to work
    public:
        Graph(const std::string& name = std::string("unnamed")) : name(name), data() {}
        Graph(const Graph&) = default; 
        bool operator<(const Graph&) const;
        void addVertex(const Vertex&);
        void addEdge(const Edge&);
        std::set<Edge> getEdgesSet() const;
        bool containsVertex(const Vertex&) const;
        bool containsEdge(const Edge&) const;

        //typedef std::map<Vertex, std::set<Vertex>>::iterator iterator; // i dont want to let users to change the data directly
        typedef std::map<Vertex, std::set<Vertex>>::const_iterator const_iterator; 
        //iterator begin();
        const_iterator begin() const;
        //iterator end();
        const_iterator end() const;

        Graph& operator=(Graph); //copies by value to avoid copying twice.
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
    
    Edge makeEdge(const Vertex&, const Vertex&);
} // namespace graph

std::ostream& operator<<(std::ostream& os, const graph::Graph& graph);

#endif // GRAPH_H
