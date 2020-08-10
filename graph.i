%module graph
%{
#include "graph.h"
%}

typedef graph::Graph* pygraph;

pygraph create();
void destroy(pygraph);

pygraph addVertex(pygraph, char* vertex);
pygraph addEdge(pygraph, char* v1, char* v2);
void disp(pygraph);

pygraph graphUnion(pygraph in1, pygraph in2, pygraph out);
pygraph graphIntersection(pygraph in1, pygraph in2, pygraph out);
pygraph graphDifference(pygraph in1, pygraph in2, pygraph out);
pygraph graphProduct(pygraph in1, pygraph in2, pygraph out);
pygraph graphComplement(pygraph in, pygraph out);
