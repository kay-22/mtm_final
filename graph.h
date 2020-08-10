#ifndef PYGRAPH_H
#define PYGRAPH_H

#include <iostream>
#include "graph/Graph.h"

graph::Graph* create();
void destroy(graph::Graph* graph);

//graph::Graph* addVertex(graph::Graph* graph, char* vertex);
graph::Graph* addEdge(graph::Graph* graph, const char* v1, const char* v2);
void disp(graph::Graph* g);

graph::Graph* graphUnion(graph::Graph* in1, graph::Graph* in2, graph::Graph* out);
graph::Graph* graphIntersection(graph::Graph* in1, graph::Graph* in2, graph::Graph* out);
graph::Graph* graphDifference(graph::Graph* in1, graph::Graph* in2, graph::Graph* out);
graph::Graph* graphProduct(graph::Graph* in1, graph::Graph* in2, graph::Graph* out);
graph::Graph* graphComplement(graph::Graph* in, graph::Graph* out);

#endif // PYGRAPH_H
 