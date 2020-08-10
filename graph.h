#ifndef PYGRAPH_H
#define PYGRAPH_H

#include <iostream>
#include "graph/Graph.h"

typedef graph::Graph* pygraph;

pygraph create();
void destroy(pygraph graph);

pygraph addVertex(pygraph graph, const char* vertex);
pygraph addEdge(pygraph graph, const char* v1, const char* v2);
void disp(pygraph g);

pygraph graphUnion(pygraph in1, pygraph in2, pygraph out);
pygraph graphIntersection(pygraph in1, pygraph in2, pygraph out);
pygraph graphDifference(pygraph in1, pygraph in2, pygraph out);
pygraph graphProduct(pygraph in1, pygraph in2, pygraph out);
pygraph graphComplement(pygraph in, pygraph out);

#endif // PYGRAPH_H
 