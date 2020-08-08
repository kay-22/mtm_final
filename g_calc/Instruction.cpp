#include "Instruction.h"

using std::map;
using std::set;
using std::string;
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

Instruction::code Declaration::execute(set<Graph>& who_set)  {return okCode;}
Instruction::code Print::execute(set<Graph>& who_set)  
{
    //string expression = openExpression(data.back());
    //const Graph& graph = evaluateExpression(expression);
    return okCode;
}
Instruction::code Delete::execute(set<Graph>& who_set) 
{
    //string graph_name = openExpression(data.back());
    // Graph graph(graph_name);

    // if (who_set.find(graph) == who_set.end()) {
    //     //throw bad variable name
    // }
    // who_set.erase(graph);

    return okCode;
}
Instruction::code Reset::execute(set<Graph>& who_set) 
{
    if (!data.back().empty()) {
        //throw found stuff after reset
    }
    who_set.clear();
    return okCode;
}
Instruction::code Quit::execute(set<Graph>& who_set)
{
    if (!data.back().empty()) {
        //throw found stuff after quit
    }
    return quitCode;
}
Instruction::code Save::execute(set<Graph>& who_set) {return okCode;}
Instruction::code Load::execute(set<Graph>& who_set) {return okCode;}
Instruction::code Empty::execute(set<Graph>& who_set) 
{
    return okCode;
}

//checks if there is at least one ('expression'). doesn't have to be enclosed.
// bool isExpressionExists(const string& expression)
// {
//     if (expression.empty()) {
//         return false;
//     }

//     Parser parser(expression);
//     string::const_iterator right_it;
//     string::const_iterator left_it = parser.findFirstPair(Instruction::EXPRESSION_BRACKET, right_it);

//     return  left_it != parser.getCurrentWord().end();
// }

//check if the expression is  ('expression') without additional expressions
// bool isEnclosedExpression(const string& expression) 
// {
    
//     if (expression.empty()) {
//         return false;
//     }

//     Parser parser(expression);
//     string::const_iterator right_it;
//     string::const_iterator left_it = parser.findFirstPair(Instruction::EXPRESSION_BRACKET, right_it);

//     return  right_it == parser.getCurrentWord().end() && 
//             left_it == parser.getCurrentWord().begin();
// }
//remove outer brackets from expression
// string openExpression(const string& expression) 
// {
//     Parser parser(expression);
//     string::const_iterator right_it;
//     string::const_iterator left_it = parser.findFirstPair(Instruction::EXPRESSION_BRACKET, right_it);

//     if (!isEnclosedExpression(expression)) {
//         //throw expression not properly enclosed with ()
//     }

//     string result(expression.begin()+1, expression.end()-1);
//     Parser::trimSideSpaces(result);

//     return result;
// }

// Graph Instruction::evaluateExpression(const string& expression, const set<Graph>& who_set)
// {
//     Parser parser(expression);
//     if(!parser.isMatchingSequence(Instruction::EXPRESSION_BRACKET)) {
//         //throw expression missing ()
//     }

//     string new_expression;

//     if (isEnclosedExpression(expression)) {
//         new_expression = openExpression(expression);
//     }

//     if (!isExpressionExists(new_expression)) {

//         evaluateSimpleExpression

//     }
//     parser = Parser(new_expression);


// }

// Graph Instruction::evaluateSimpleExpression(const string& expression, const set<Graph>& who_set) 
// {
//     if (isalnum(expression.front() )
// }