#include "graph.h"

using graph::Graph;
using graph::Vertex;
using graph::Edge;
using graph::makeEdge;
using graph::Exception;
using std::cout;
using std::endl;

pygraph create()
{
    return new Graph();
}

void destroy(pygraph graph)
{
    delete graph;
}

pygraph addVertex(pygraph graph, const char* vertex)
{
    pygraph result = graph;

    try{
        graph->addVertex(Vertex(vertex));
    }
    catch (const Exception& e) {
        cout << e.what() << endl;
        result = nullptr;
    }
    return result;
}
pygraph addEdge(pygraph graph, const char* v1, const char* v2)
{
    pygraph result = graph;
    try {
        const Edge& edge = makeEdge(Vertex(v1), Vertex(v2));
        graph->addEdge(edge);
    }
    catch (const graph::Exception& e) {
        cout << e.what() << endl;
        result = nullptr;
    }

    return result;
}

void disp(pygraph graph)
{
    cout << *graph << endl;
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
