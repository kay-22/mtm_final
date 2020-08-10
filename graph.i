%module graph
%{
#include "graph.h"
using namespace graph;
typedef graph::Graph* pygraph;
%}

%include "graph.h"