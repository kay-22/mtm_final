#ifndef GRAPH_CALCULATOR_H
#define GRAPH_CALCULATOR_H

#include <set>
#include <fstream>
#include <memory>

#include <graph.h>
#include <g_utility.h>
#include "Instruction.h"

namespace graph
{
    class GraphCalculator 
    {
    private:
        std::set<Graph> who_set;
    public:
        GraphCalculator() = default;
        GraphCalculator(const GraphCalculator&) = delete;
        GraphCalculator& operator=(const GraphCalculator&) = delete;
        ~GraphCalculator() = default;

        //run interactive interpreter
        void run();
        //run automatic interpreter
        void runBatch(const std::ifstream& input, std::ofstream& output);
    };
} // namespace graph


#endif // GRAPH_CALCULATOR_H