#ifndef PYGRAPH_H
#define PYGRAPH_H

#include <iostream>
#include "graph/Graph.h"

typedef graph::Graph* pygraph;

pygraph create();
void destroy(pygraph graph);

pygraph addVertex(pygraph graph, char* vertex);
pygraph addEdge(pygraph graph, char* v1, char* v2);
void disp(pygraph graph);

pygraph graphUnion(pygraph in1, pygraph in2, pygraph out);
pygraph graphIntersection(pygraph in1, pygraph in2, pygraph out);
pygraph graphDifference(pygraph in1, pygraph in2, pygraph out);
pygraph graphProduct(pygraph in1, pygraph in2, pygraph out);
pygraph graphComplement(pygraph in, pygraph out);

#endif // PYGRAPH_H
 