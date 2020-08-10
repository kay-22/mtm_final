#include "graph.h"

//using graph::Graph;
//using graph::Vertex;
//using graph::Edge;
//using graph::makeEdge;
//using graph::Exception;
//using std::cout;
//using std::endl;

pygraph create()
{
    return new graph::Graph();
}

void destroy(pygraph graph)
{
    delete graph;
}

pygraph addVertex(pygraph graph, const char* vertex)
{
    pygraph result = graph;

    try{
        graph->addVertex(graph::Vertex(vertex));
    }
    catch (const graph::Exception& e) {
        std::cout << e.what() << std::endl;
        result = nullptr;
    }
    return result;
}
pygraph addEdge(pygraph graph, char* v1, const char* v2)
{
    pygraph result = graph;
    try {
        const std::pair<graph::Vertex, graph::Vertex>& edge = makeEdge(graph::Vertex(v1), graph::Vertex(v2));
        graph->addEdge(edge);
    }
    catch (const graph::Exception& e) {
        std::cout << e.what() << std::endl;
        result = nullptr;
    }

    return result;
}

void disp(pygraph graph)
{
    std::cout << *graph << std::endl;
}

pygraph graphUnion(pygraph in1, pygraph in2, pygraph out)
{
    *out = *in1 + *in2;
    return out;
}

pygraph graphIntersection(pygraph in1, pygraph in2, pygraph out)
{
    *out = *in1 ^ *in2;
    return out;
}

pygraph graphDifference(pygraph in1, pygraph in2, pygraph out)
{
    *out = *in1 - *in2;
    return out;
}

pygraph graphProduct(pygraph in1, pygraph in2, pygraph out)
{
    *out = (*in1) * (*in2);
    return out;
}

pygraph graphComplement(pygraph in, pygraph out)
{
    *out = !(*in);
    return out;
}
