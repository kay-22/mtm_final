#include "GraphCalculator.h"

using std::ifstream;
using std::ofstream;
using std::istream;
using std::string;
using std::set;
using std::vector;
using std::shared_ptr;
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using graph::GraphCalculator;
using graph::Instruction;
using graph::Parser;

static const string PROMPT("Gcalc> ");

void GraphCalculator::run()
{
    
    Instruction::code instruction_code = Instruction::code::okCode;
    while (instruction_code != Instruction::code::quitCode) {
        cout << PROMPT;
        Parser parser(cin);
        shared_ptr<Instruction> instruction = parser.makeInstructions().back(); //cin should only make one instruction at aTIME

        try {
            instruction_code = instruction->execute(who_set, cout);               

        }
        catch(const graph::Exception& e) { 
            cout << e.what() << endl;
        }
        catch(const std::exception& e) {
            cerr << "Error: fatal error occured --" << e.what() << endl;
            throw;
        }

    }
}

void GraphCalculator::runBatch(ifstream& input, ofstream& output) 
{
    Parser parser(input);
    vector<shared_ptr<Instruction>> instructions = parser.makeInstructions();

    int line_num = 1;
    for (auto instruction : instructions) {
        try {
            if (instruction->execute(who_set, output) == Instruction::quitCode) {
                break;
            }

        }
        catch(const graph::Exception& e) { 
            output << e.what() << " (at line #" << line_num << ")" << endl;
        }
        catch(const std::exception& e) {
            cerr << "Error: fatal error occured --" << e.what() << endl;
            throw;
        }

        line_num++;
    }
}