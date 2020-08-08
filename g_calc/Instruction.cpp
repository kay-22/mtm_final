#include "Instruction.h"

using std::map;
using std::set;
using std::vector;
using std::string;
using std::ostream;
using std::endl;
using graph::Instruction;
using graph::Declaration;
using graph::Quit;
using graph::Reset;
using graph::Delete;
using graph::Print;
using graph::Save;
using graph::Load;
using graph::Empty;
using graph::BracketPattern;
using graph::Parser;
using graph::Graph;

const char Declaration::DECLARATION_CHAR = '=';
const BracketPattern Instruction::EXPRESSION_BRACKET('(',')');
const map<Instruction::keyword, string> Instruction::KEYWORDS = {
                                                                    {PRINT, "print"}, 
                                                                    {DELETE, "delete"},
                                                                    {RESET, "reset"}, 
                                                                    {QUIT, "quit"}, 
                                                                    {SAVE, "save"}, 
                                                                    {LOAD, "load"}
                                                                };

//static string openExpression(const string& expression);
//static bool isExpressionExists(const string& expression);
//static bool isEnclosedExpression(const string& expression);
static Graph evaluateExpression(const string& expression, const std::set<Graph>& who_set);

Instruction::code Declaration::execute(set<Graph>& who_set, ostream& out)  {return okCode;}
Instruction::code Print::execute(set<Graph>& who_set, ostream& out)
{
    Parser parser(data.back());
    parser.openExpression();

    const Graph& graph = evaluateExpression(parser.getCurrentWord(), who_set);

    out << graph << endl;

    return okCode;
}
Instruction::code Delete::execute(set<Graph>& who_set, ostream& out) 
{
    
    Parser parser(data.back());
    parser.openExpression();
    Graph graph(parser.getCurrentWord());

    if (who_set.find(graph) == who_set.end()) {
        //throw bad variable name
    }
    who_set.erase(graph);

    return okCode;
}
Instruction::code Reset::execute(set<Graph>& who_set, ostream& out) 
{
    if (!data.back().empty()) {
        //throw found stuff after reset
    }
    who_set.clear();
    return okCode;
}
Instruction::code Quit::execute(set<Graph>& who_set, ostream& out)
{
    if (!data.back().empty()) {
        //throw found stuff after quit
    }
    return quitCode;
}
Instruction::code Save::execute(set<Graph>& who_set, ostream& out) {return okCode;}
Instruction::code Load::execute(set<Graph>& who_set, ostream& out) {return okCode;}
Instruction::code Empty::execute(set<Graph>& who_set, ostream& out) 
{
    return okCode;
}


Graph evaluateExpression(const string& expression, const set<Graph>& who_set)
{
    Parser parser(expression);
    vector<string> expression_data = parser.getExpressionData();

    return Graph();
}

// Graph Instruction::evaluateSimpleExpression(const string& expression, const set<Graph>& who_set) 
// {
//     if (isalnum(expression.front() )
// }