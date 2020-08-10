#include "Graph.h"

using graph::Graph;
using graph::Vertex;
using graph::Edge;
using graph::Parser;
using std::map;
using std::set;
using std::make_pair;
using std::swap;
//using std::vector;
//using std::generate;
using std::string;

// const char Graph::OperationCharacters::UNION = '+';
// const char Graph::OperationCharacters::INTERSECTION = '^';
// const char Graph::OperationCharacters::DIFFERENCE = '-';
// const char Graph::OperationCharacters::PRODUCT = '*';
// const char Graph::OperationCharacters::COMPLEMENT ='!';

Parser::SpecialCharacters Graph::OperationCharacters::toSpecialChars()
{
    return Parser::SpecialCharacters({UNION, INTERSECTION, DIFFERENCE, PRODUCT, COMPLEMENT});
}


void Graph::addVertex(const Vertex& vertex)
{
    if (containsVertex(vertex)) {
        throw GraphExsitingElementException("vertex '" + vertex.getName()+"' already exits.");
    }
    data.insert(make_pair(vertex, set<Vertex>()));
}

void Graph::addEdge(const Edge& edge)
{
    if (containsEdge(edge)) {
        throw GraphExsitingElementException("edge <" + 
            edge.first.getName() + ", " + edge.second.getName() + "> already exits.");
    }

    if(edge.first == edge.second) {
        throw GraphException("graph cannot have loops");
    }

    //const Vertex* to_ptr = &data.find(to_vertex)->first;
    data.at(edge.first).insert(edge.second);
}

set<Edge> Graph::getEdgesSet() const
{
    set<Edge> result;

    for (const auto& vertex_data : data) {
        const Vertex& source_vertex = vertex_data.first;

        for(const Vertex& dest_vertex : vertex_data.second) {
            Edge edge = makeEdge(source_vertex, dest_vertex);
            result.insert(edge);
        }
    }

    return result;
}

const string& Graph::getName() const
{
    return name.toString();
}

bool Graph::containsVertex(const Vertex& vertex) const
{
    return data.find(vertex) != data.end();
}

bool Graph::containsEdge(const Edge& edge) const
{
    if (!containsVertex(edge.first)) {
        throw GraphNoElementException("vertex '" + edge.first.getName() + "' does not exit.");
    }
    if (!containsVertex(edge.second)) {
        throw GraphNoElementException("vertex '" + edge.second.getName() + "' does not exit.");
    }
    //const Vertex* to_ptr = &data.find(to_vertex)->first;
    
    return data.at(edge.first).find(edge.second) != data.at(edge.first).end();
}

string Graph::makeLiteral() const
{
    string result("{"); //update later literals to Parser::GRAPH_BRACKET
    string edges("|");

    for (const auto& vertex_data : data) {
        const Vertex& vertex_i = vertex_data.first;
        result += vertex_i.getName() + ",";

        for (const Vertex& vertex_j : vertex_data.second) {
            edges += "<" + vertex_i.getName() + "," + vertex_j.getName() + ">,";
        }
    }
    if (!data.empty()){    
        result.pop_back(); // remove last ','
        edges.pop_back(); //      ^
    }
    result += edges + "}";

    return result;
}

// Graph::iterator Graph::begin()
// {
//     return data.begin();
// }

Graph::const_iterator Graph::begin() const
{
    return data.begin();
}

// Graph::iterator Graph::end()
// {
//     return data.end();
// }

Graph::const_iterator Graph::end() const
{
    return data.end();
}

int Graph::size() const
{
    return data.size();
}

Graph& Graph::operator=(Graph copy)
{
    swap(data, copy.data); //swappable?
    return *this;
}

bool Graph::operator<(const Graph& other) const
{
    return name < other.name;
}

Graph Graph::operator+(const Graph& other_graph) const
{
    Graph result = *this;

    for (const auto& other_vertex_data : other_graph.data) {
        //unite all vertices without edges
        try {
            result.addVertex(other_vertex_data.first);
        }
        catch (const GraphExsitingElementException& e) {
            //ignore existing vertices
        }
    }
    for (const auto& other_vertex_data : other_graph.data) {
        //unite all edges
        auto it = result.data.find(other_vertex_data.first);
        
        // #ifndef NDEBUG
        // #include <cassert>
        // assert(it!=result.data.end());
        // #endif

        it->second.insert(other_vertex_data.second.begin(), other_vertex_data.second.end()); 
    }
    
    return result;
}

Graph Graph::operator^(const Graph& other_graph) const
{
    Graph result;
    
    for (const auto& other_vertex_data : other_graph.data) {
        //intersect vertices without edges
        if (containsVertex(other_vertex_data.first)) {
            result.addVertex(other_vertex_data.first);
        }
    }

    for (const auto& result_vertex_data : result.data) {
        //intersect edges
        const Vertex& vertex_i = result_vertex_data.first;

        for (const auto& result_other_vertex_data : result.data) {
            //possible to iterate from result.data.frind(vertex_i) because set is ordered. maybe change later.
            const Vertex& vertex_j = result_other_vertex_data.first;
            if (vertex_i == vertex_j) {
                continue;
            }
            Edge edge_ij = makeEdge(vertex_i, vertex_j);
            if (containsEdge(edge_ij) && other_graph.containsEdge(edge_ij)) {
                result.addEdge(edge_ij);
            }
        }

    }

    return result;
}

Graph Graph::operator-(const Graph& other_graph) const 
{
    Graph result;

    for (const auto& vertex_data : data) {
        //difference of vertices without edges first (can't add edges to vertices that are not in the graph)
        if (!other_graph.containsVertex(vertex_data.first)) {
            result.addVertex(vertex_data.first);
        }
    }

    for (const auto& result_vertex_data : result.data) {
    //difference of edges
        const Vertex& vertex_i = result_vertex_data.first;

        for (const auto& result_other_vertex_data : result.data) {
            //possible to iterate from result.data.frind(vertex_i) because set is ordered. maybe change later.
            const Vertex& vertex_j = result_other_vertex_data.first;
            if (vertex_i == vertex_j) {
                continue;
            }

            Edge edge_ij = makeEdge(vertex_i, vertex_j);
            if (containsEdge(edge_ij)) {
                result.addEdge(edge_ij);
            }
        }
    }

    return result;
}

Graph Graph::operator*(const Graph& other_graph) const
{
    Graph result;

    char left_bracket = Parser::VERTEX_BRACKET.left;
    char right_bracket = Parser::VERTEX_BRACKET.right;
    char delimiter = Parser::VERTEX_BRACKET.delimiter;

    for (const auto& vertex_data : data) {
        //product of vertices without edges
        const Vertex& vertex_i = vertex_data.first;

        for (const auto& other_vertex_data :other_graph.data) {
            const Vertex& vertex_j = other_vertex_data.first;
            Vertex result_vertix(left_bracket + vertex_i.getName() + delimiter + vertex_j.getName() + right_bracket);
            result.addVertex(result_vertix);
        }
    }

    for (const Edge& edge_i : getEdgesSet()) {
        //product of edges
        for (const Edge& edge_j : other_graph.getEdgesSet()) {
            if (edge_i == edge_j) {
                continue;
            }
            Vertex source_vertex(left_bracket + 
                                 edge_i.first.getName() + delimiter + edge_j.first.getName() + 
                                 right_bracket);
            Vertex dest_vertex(left_bracket + 
                                edge_i.second.getName() + delimiter + edge_j.second.getName() + 
                                right_bracket);
            
            result.data.at(source_vertex).insert(dest_vertex);
        }
    }

    return result;
}

Graph Graph::operator!() const
{
    Graph result;
    set<Edge> edges_set = getEdgesSet();

    for (const auto& vertex_data : data) {
        //adds only the vertices
        result.addVertex(vertex_data.first);
    }

    for (const auto& vertex_i_data : data) {
        //adds the complement edges
        const Vertex& vertex_i = vertex_i_data.first;
        
        for (const auto& vertex_j_data : data) {
            const Vertex& vertex_j = vertex_j_data.first;

            Edge edge_ij = makeEdge(vertex_i, vertex_j);
            if (vertex_i == vertex_j || containsEdge(edge_ij)){
                continue;
            }
            
            result.addEdge(edge_ij);
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const Graph& graph)
{
    string result;

    for(const auto& vertex_data : graph) {
        //vertices
        result += vertex_data.first.getName() + '\n';
    }
    result += '$';

    set<Edge> edges_set = graph.getEdgesSet();
    for (const Edge& edge : edges_set) {
        //edges
        result += '\n' + edge.first.getName() + ' ' + edge.second.getName();
    }

    os << result;

    return os;
}

Graph graph::makeGraph(const string& graph_literal, const string& graph_name)
{
    Graph result(graph_name);
    Parser parser(graph_literal);

    Parser::GraphLiteralData graph_data = parser.decomposeGraphLiteral();
    Parser::GraphVerticesData vertices_data = graph_data.first;
    Parser::GraphEdgesData edges_data = graph_data.second;

    for (const string& vertex_datum : vertices_data) {
        Vertex vertex(vertex_datum);
        result.addVertex(vertex);
    }

    for (const auto& edge_datum : edges_data) {
        const Vertex& vertex_from = edge_datum.first;
        const Vertex& vertex_to = edge_datum.second;
        result.addEdge(makeEdge(vertex_from, vertex_to));
    }

    return result;
}

Edge graph::makeEdge(const Vertex& from, const Vertex& to)
{
    //return make_pair(from, to);
    return Edge(from, to);
}
//needs Vertex() to work
// vector<Vertex> Graph::getVertices() const
// {
//     vector<Vertex> vertices(data.size());
//     auto it = data.begin();
//     generate(vertices.begin(), vertices.end(), [&it](){return (it++)->first;}); //post-increment?

//     return vertices;
// }

bool Edge::operator==(const Edge& other) const
{
    return first==other.first && second==other.second;
}

bool Edge::operator<(const Edge& other) const
{
    if (first<other.first) {
        return true;
    }
    else if (other.first <first) {
        return false;
    }
    else if (second < other.second) {
        return true;
    }
    
    return false;
}