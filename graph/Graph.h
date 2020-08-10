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
#include "../g_utility/GraphName.h"
#include "../g_except/GraphException.h"
#include "../g_utility/Parser.h"

namespace graph
{
    
    //typedef std::pair<Vertex, Vertex> Edge;
    struct Edge;
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
        const std::string& getName() const;
        bool containsVertex(const Vertex&) const;
        bool containsEdge(const Edge&) const;
        std::string makeLiteral() const;

        //typedef std::map<Vertex, std::set<Vertex>>::iterator iterator; // i dont want to let users to change the data directly
        typedef std::map<Vertex, std::set<Vertex>>::const_iterator const_iterator; 
        //iterator begin();
        const_iterator begin() const;
        //iterator end();
        const_iterator end() const;
        int size() const;

        Graph& operator=(Graph); //copies by value to avoid copying twice.
        //Graph& operator+=(const Graph&);
        //maybe implement ^= -= += and make binary non-member
        //idont think i need binary ops if no other types are needed to be casted (rip engligh)
        Graph operator+(const Graph&) const;
        Graph operator^(const Graph&) const;
        Graph operator-(const Graph&) const;
        Graph operator*(const Graph&) const;
        Graph operator!() const;

        struct OperationCharacters 
        {
            static const char UNION = '+';
            static const char INTERSECTION = '^';
            static const char DIFFERENCE = '-';
            static const char PRODUCT = '*';
            static const char COMPLEMENT ='!';
            
            static Parser::SpecialCharacters toSpecialChars();
        };

        ~Graph() = default;
    }; 

    //makes a graph from a literal graph strign and throws appropriate exceptions
    Graph makeGraph(const std::string& graph_literal, const std::string& graph_name = "unnamed");
    Edge makeEdge(const Vertex&, const Vertex&);

    struct Edge 
    {
    public:
        Vertex first;
        Vertex second;
        Edge(const Vertex& first, const Vertex& second) : first(first), second(second) {}
        bool operator<(const Edge& other) const;
        bool operator==(const Edge& other) const;
    };
} // namespace graph

std::ostream& operator<<(std::ostream& os, const graph::Graph& graph);

#endif // GRAPH_H
