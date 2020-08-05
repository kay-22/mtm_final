#include "Graph.h"

using graph::Graph;
using graph::Vertex;
using std::map;
using std::set;
using std::vector;
using std::generate;

bool Graph::operator<(const Graph& other) const
{
    return name < other.name;
}

Graph Graph::operator+(const Graph& other_graph) const
{
    Graph result = *this;

    for (auto other_vertice_data : other_graph.graph)
    {
        auto it = result.graph.find(other_vertice_data.first);

        if (it == graph.end()) {
            result.graph.insert(*it); //new vertex
        }
        else {
            // add edges to existing vertex
            it->second.insert(other_vertice_data.second.begin(), other_vertice_data.second.end()); 
        }
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