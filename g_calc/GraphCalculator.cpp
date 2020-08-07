#include "GraphCalculator.h"

using std::ifstream;
using std::ofstream;
using std::set;
using std::vector;
using std::shared_ptr;
using graph::GraphCalculator;
using graph::Instruction;
using graph::Parser;

void GraphCalculator::runBatch(const ifstream& input, ofstream& output) 
{
    Parser parser(input);
    vector<shared_ptr<Instruction>> instructions = parser.makeInstructions();

    for (auto instruction : instructions) {
        try {
            if (instruction->execute() == Instruction::QUIT) {
                break;
            }

        }
        catch (...) { //update exceptiond

        }
    }
}