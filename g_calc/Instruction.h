#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

#include <graph/Graph.h>

namespace graph
{
    class Instruction 
    //abstruct base class that executes instuctions on a given graph calculator
    {
    protected:
        std::set<Graph> instructees;
    public:
        enum code{QUIT};
        Instruction(std::set<Graph>& instructees) : instructees(instructees) {}
        virtual code execute() = 0;
    };

    class Command : Instruction
    {
    protected:
        std::string keyword;
    public:
    
    };

    class Delete : Command
    {

    };
} // namespace graph


#endif // INSTRUCTION_H
