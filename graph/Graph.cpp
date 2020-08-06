#include "Graph.h"

using graph::Graph;
using graph::Vertex;
using std::map;
using std::set;
using std::make_pair;
//using std::vector;
using std::generate;

void Graph::addVertex(const Vertex& vertex)
{
    if (containsVertex(vertex)) {
        //throw already exists
    }
    graph.insert(make_pair(vertex, set<const Vertex*>()));
}

void Graph::addEdge(const Vertex& from_vertex, const Vertex& to_vertex)
{
    if (containsEdge(from_vertex, to_vertex)) {
        //trhow already exists
    }

    const Vertex* to_ptr = &graph.find(to_vertex)->first;
    graph.at(from_vertex).insert(to_ptr);
}

bool Graph::containsVertex(const Vertex& vertex) const
{
    return graph.find(vertex) != graph.end();
}

bool Graph::containsEdge(const Vertex& from_vertex, const Vertex& to_vertex) const
{
    if (!containsVertex(from_vertex) || !containsVertex(to_vertex)) {
        //trhow no such vertex
    }
    const Vertex* to_ptr = &graph.find(to_vertex)->first;
    
    return graph.at(from_vertex).find(to_ptr) != graph.at(from_vertex).end();
}

bool Graph::operator<(const Graph& other) const
{
    return name < other.name;
}

Graph Graph::operator+(const Graph& other_graph) const
{
    Graph result = *this;

    for (auto other_vertex_data : other_graph.graph) {
        //unite all vertices without edges
        try {
            result.addVertex(other_vertex_data.first);
        }
        catch (...) {//change to appropriate except
            //ignore existing vertices
        }
    }
    for (auto other_vertex_data : other_graph.graph) {
        //unite all edges
        auto it = result.graph.find(other_vertex_data.first);
        
        #ifndef NDEBUG
        #include <cassert>
        assert(it!=result.graph.end());
        #endif

        it->second.insert(other_vertex_data.second.begin(), other_vertex_data.second.end()); 
    }
    
    return result;
}

//needs Vertex() to work
// vector<Vertex> Graph::getVertices() const
// {
//     vector<Vertex> vertices(graph.size());
//     auto it = graph.begin();
//     generate(vertices.begin(), vertices.end(), [&it](){return (it++)->first;}); //post-increment?

//     return vertices;
// }