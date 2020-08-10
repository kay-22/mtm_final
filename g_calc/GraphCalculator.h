#ifndef GRAPH_CALCULATOR_H
#define GRAPH_CALCULATOR_H

#include <set>
#include <fstream>
#include <iostream>
#include <memory>
#include <exception>

#include "../graph/Graph.h"
#include "../g_utility/Parser.h"
#include "../g_except/Exception.h"
#include "../g_except/GraphException.h"
#include "../g_except/InstructionException.h"
#include "../g_except/NameException.h"
#include "../g_except/ParserException.h"

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
        void runBatch(std::ifstream& input, std::ofstream& output);
    };
} // namespace graph


#endif // GRAPH_CALCULATOR_H
